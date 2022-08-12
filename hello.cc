//
// Based on v8's samples/hello-world.cc:
//
// Copyright 2014 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#include <iostream>

#include <libplatform/libplatform.h>
#include <v8.h>

int
main (int argc,
      char * argv[])
{
  auto platform = v8::platform::NewDefaultPlatform ();
  v8::V8::InitializePlatform (platform.get ());
  v8::V8::Initialize ();

  v8::Isolate::CreateParams create_params;
  create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator ();
  auto isolate = v8::Isolate::New (create_params);

  {
    v8::Isolate::Scope isolate_scope (isolate);
    v8::HandleScope handle_scope (isolate);
    auto context = v8::Context::New (isolate);
    v8::Context::Scope context_scope (context);

    auto source = v8::String::NewFromUtf8 (isolate, "'Hello' + ', V8!'", v8::NewStringType::kNormal).ToLocalChecked ();
    auto script = v8::Script::Compile (context, source).ToLocalChecked ();
    auto result = script->Run (context).ToLocalChecked ();

    v8::String::Utf8Value str (isolate, result);
    std::cout << *str << std::endl;
  }

  isolate->Dispose ();

  v8::V8::Dispose ();
  v8::V8::DisposePlatform ();
  delete create_params.array_buffer_allocator;

  return 0;
}
