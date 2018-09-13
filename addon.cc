#include <node_api.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

napi_value Srand(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 1;
  napi_value args[1];
  status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  assert(argc == 1);

  napi_valuetype valuetype;
  status = napi_typeof(env, args[0], &valuetype);
  assert(status == napi_ok);

  assert(valuetype == napi_number);

  uint32_t value;
  status = napi_get_value_uint32(env, args[0], &value);
  assert(status == napi_ok);

  srand(value);

  napi_value undef;
  status = napi_get_undefined(env, &undef);
  assert(status == napi_ok);

  return undef;
}

napi_value Rand(napi_env env, napi_callback_info info) {
  napi_status status;

  int value = rand();

  napi_value result;
  status = napi_create_int64(env, value, &result);
  assert(status == napi_ok);

  return result;
}

#define DECLARE_NAPI_METHOD(name, func) \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor descs[] = {
    DECLARE_NAPI_METHOD("srand", Srand),
    DECLARE_NAPI_METHOD("rand", Rand)
  };
  status = napi_define_properties(env, exports, 2, descs);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
