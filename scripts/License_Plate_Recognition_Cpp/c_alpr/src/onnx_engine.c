#include "onnx_engine.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef ALPR_USE_ONNXRUNTIME
#include <onnxruntime_c_api.h>
#endif

struct AlprOnnxEngine {
    int use_gpu;
#ifdef ALPR_USE_ONNXRUNTIME
    const OrtApi* api;
    OrtEnv* env;
    OrtSessionOptions* session_options;
    OrtSession* session;
    OrtMemoryInfo* mem_info;
#endif
};

#ifdef ALPR_USE_ONNXRUNTIME
static int check_status(AlprOnnxEngine* e, OrtStatus* status) {
    if (!status) {
        return 0;
    }

    if (e && e->api) {
        const char* msg = e->api->GetErrorMessage(status);
        if (msg) {
            fprintf(stderr, "[onnxruntime] %s\n", msg);
        }
    }

    e->api->ReleaseStatus(status);
    return -1;
}
#endif

AlprOnnxEngine* alpr_onnx_create(const char* model_path, int use_gpu) {
    AlprOnnxEngine* e = (AlprOnnxEngine*)calloc(1, sizeof(AlprOnnxEngine));
    if (!e) {
        return NULL;
    }
    e->use_gpu = use_gpu;

#ifdef ALPR_USE_ONNXRUNTIME
    e->api = OrtGetApiBase()->GetApi(ORT_API_VERSION);
    if (!e->api) {
        free(e);
        return NULL;
    }

    if (check_status(e, e->api->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "c_alpr", &e->env)) != 0) {
        free(e);
        return NULL;
    }

    if (check_status(e, e->api->CreateSessionOptions(&e->session_options)) != 0) {
        e->api->ReleaseEnv(e->env);
        free(e);
        return NULL;
    }

    (void)e->api->SetIntraOpNumThreads(e->session_options, 1);
    (void)e->api->SetSessionGraphOptimizationLevel(e->session_options, ORT_ENABLE_ALL);

#ifdef _WIN32
    wchar_t model_path_w[1024];
    int wlen = MultiByteToWideChar(CP_UTF8, 0, model_path, -1, model_path_w, (int)(sizeof(model_path_w) / sizeof(model_path_w[0])));
    if (wlen <= 0) {
        e->api->ReleaseSessionOptions(e->session_options);
        e->api->ReleaseEnv(e->env);
        free(e);
        return NULL;
    }

    if (check_status(e, e->api->CreateSession(e->env, model_path_w, e->session_options, &e->session)) != 0) {
#else
    if (check_status(e, e->api->CreateSession(e->env, model_path, e->session_options, &e->session)) != 0) {
#endif
        e->api->ReleaseSessionOptions(e->session_options);
        e->api->ReleaseEnv(e->env);
        free(e);
        return NULL;
    }

    if (check_status(e, e->api->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &e->mem_info)) != 0) {
        e->api->ReleaseSession(e->session);
        e->api->ReleaseSessionOptions(e->session_options);
        e->api->ReleaseEnv(e->env);
        free(e);
        return NULL;
    }
#else
    (void)model_path;
#endif

    return e;
}

void alpr_onnx_destroy(AlprOnnxEngine* engine) {
    if (!engine) {
        return;
    }

#ifdef ALPR_USE_ONNXRUNTIME
    if (engine->api) {
        if (engine->mem_info) {
            engine->api->ReleaseMemoryInfo(engine->mem_info);
        }
        if (engine->session) {
            engine->api->ReleaseSession(engine->session);
        }
        if (engine->session_options) {
            engine->api->ReleaseSessionOptions(engine->session_options);
        }
        if (engine->env) {
            engine->api->ReleaseEnv(engine->env);
        }
    }
#endif

    free(engine);
}

void alpr_onnx_output_free(AlprOnnxOutput* out) {
    if (!out) {
        return;
    }
    if (out->data) {
        free(out->data);
    }
    memset(out, 0, sizeof(*out));
}

int alpr_onnx_run(
    AlprOnnxEngine* engine,
    const float* input_chw,
    int input_w,
    int input_h,
    int input_c,
    AlprOnnxOutput* out
) {
    if (!engine || !input_chw || input_w <= 0 || input_h <= 0 || input_c <= 0 || !out) {
        return -1;
    }

    memset(out, 0, sizeof(*out));

#ifdef ALPR_USE_ONNXRUNTIME
    OrtStatus* status = NULL;
    OrtAllocator* allocator = NULL;
    OrtValue* input_tensor = NULL;
    OrtValue* output_tensor = NULL;
    char* input_name = NULL;
    char* output_name = NULL;

    status = engine->api->GetAllocatorWithDefaultOptions(&allocator);
    if (check_status(engine, status) != 0) {
        return -2;
    }

    status = engine->api->SessionGetInputName(engine->session, 0, allocator, &input_name);
    if (check_status(engine, status) != 0) {
        return -3;
    }
    status = engine->api->SessionGetOutputName(engine->session, 0, allocator, &output_name);
    if (check_status(engine, status) != 0) {
        allocator->Free(allocator, input_name);
        return -4;
    }

    long long input_shape[4];
    input_shape[0] = 1;
    input_shape[1] = input_c;
    input_shape[2] = input_h;
    input_shape[3] = input_w;
    size_t input_len = (size_t)input_c * (size_t)input_h * (size_t)input_w;

    status = engine->api->CreateTensorWithDataAsOrtValue(
        engine->mem_info,
        (void*)input_chw,
        input_len * sizeof(float),
        input_shape,
        4,
        ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT,
        &input_tensor
    );
    if (check_status(engine, status) != 0) {
        allocator->Free(allocator, input_name);
        allocator->Free(allocator, output_name);
        return -5;
    }

    const char* input_names[] = { input_name };
    const char* output_names[] = { output_name };

    status = engine->api->Run(
        engine->session,
        NULL,
        input_names,
        (const OrtValue* const*)&input_tensor,
        1,
        output_names,
        1,
        &output_tensor
    );
    if (check_status(engine, status) != 0) {
        engine->api->ReleaseValue(input_tensor);
        allocator->Free(allocator, input_name);
        allocator->Free(allocator, output_name);
        return -6;
    }

    OrtTensorTypeAndShapeInfo* shape_info = NULL;
    status = engine->api->GetTensorTypeAndShape(output_tensor, &shape_info);
    if (check_status(engine, status) != 0) {
        engine->api->ReleaseValue(output_tensor);
        engine->api->ReleaseValue(input_tensor);
        allocator->Free(allocator, input_name);
        allocator->Free(allocator, output_name);
        return -7;
    }

    size_t rank = 0;
    status = engine->api->GetDimensionsCount(shape_info, &rank);
    if (check_status(engine, status) != 0 || rank > ALPR_MAX_TENSOR_DIMS) {
        engine->api->ReleaseTensorTypeAndShapeInfo(shape_info);
        engine->api->ReleaseValue(output_tensor);
        engine->api->ReleaseValue(input_tensor);
        allocator->Free(allocator, input_name);
        allocator->Free(allocator, output_name);
        return -8;
    }

    long long dims[ALPR_MAX_TENSOR_DIMS];
    status = engine->api->GetDimensions(shape_info, dims, rank);
    if (check_status(engine, status) != 0) {
        engine->api->ReleaseTensorTypeAndShapeInfo(shape_info);
        engine->api->ReleaseValue(output_tensor);
        engine->api->ReleaseValue(input_tensor);
        allocator->Free(allocator, input_name);
        allocator->Free(allocator, output_name);
        return -9;
    }

    size_t total = 1;
    for (size_t i = 0; i < rank; i++) {
        if (dims[i] <= 0) {
            total = 0;
            break;
        }
        total *= (size_t)dims[i];
    }

    float* output_ptr = NULL;
    status = engine->api->GetTensorMutableData(output_tensor, (void**)&output_ptr);
    if (check_status(engine, status) != 0 || !output_ptr || total == 0) {
        engine->api->ReleaseTensorTypeAndShapeInfo(shape_info);
        engine->api->ReleaseValue(output_tensor);
        engine->api->ReleaseValue(input_tensor);
        allocator->Free(allocator, input_name);
        allocator->Free(allocator, output_name);
        return -10;
    }

    out->data = (float*)malloc(total * sizeof(float));
    if (!out->data) {
        engine->api->ReleaseTensorTypeAndShapeInfo(shape_info);
        engine->api->ReleaseValue(output_tensor);
        engine->api->ReleaseValue(input_tensor);
        allocator->Free(allocator, input_name);
        allocator->Free(allocator, output_name);
        return -11;
    }

    memcpy(out->data, output_ptr, total * sizeof(float));
    out->data_len = total;
    out->rank = rank;
    for (size_t i = 0; i < rank; i++) {
        out->shape[i] = dims[i];
    }

    engine->api->ReleaseTensorTypeAndShapeInfo(shape_info);
    engine->api->ReleaseValue(output_tensor);
    engine->api->ReleaseValue(input_tensor);
    allocator->Free(allocator, input_name);
    allocator->Free(allocator, output_name);
    return 0;
#else
    (void)engine;
    (void)input_chw;
    (void)input_w;
    (void)input_h;
    (void)input_c;
    (void)out;
    return -1;
#endif
}
