/*
 *  Copyright 2008-2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/*! \file malloc.h
 *  \brief CUDA implementation of device malloc.
 */

#pragma once

#include <thrust/detail/config.h>
#include <thrust/device_ptr.h>

namespace thrust
{

namespace detail
{

namespace backend
{

namespace cuda
{

template<unsigned int DummyParameterToPreventInstantiation>
thrust::device_ptr<void> malloc(const std::size_t n);

} // end namespace cuda

} // end namespace backend

} // end namespace detail

} // end namespace thrust

#include <thrust/detail/backend/cuda/malloc.inl>

