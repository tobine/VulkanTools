#! /usr/bin/python3

# Copyright (C) 2018 Valve Corporation
# Copyright (C) 2018 LunarG, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Author: Mike Weiblen <mikew@lunarg.com>

# Inspired by https://github.com/gabdube/python-vulkan-triangle

import platform, sys
from ctypes import c_void_p, c_float, c_uint8, c_uint, c_uint64, c_int, c_size_t, c_char, c_char_p, cast, Structure, POINTER, pointer, byref

# Platform library handling #################################################

platform_name = platform.system()
if platform_name == 'Windows':
    from ctypes import WINFUNCTYPE, windll
    FUNCTYPE = WINFUNCTYPE
    vk = windll.LoadLibrary('vulkan-1')
elif platform_name == 'Linux':
    from ctypes import CFUNCTYPE, cdll
    FUNCTYPE = CFUNCTYPE
    vk = cdll.LoadLibrary('libvulkan.so.1')
else:
    raise RuntimeError('Unsupported platform "{}"'.format(platform_name))

def GetFunctions(vk_object, function_list, get_proc_addr):
    result = []
    for name, return_type, *args in function_list:
        py_name = name.decode()
        fn_ptr = get_proc_addr(vk_object, name)
        fn_ptr = cast(fn_ptr, c_void_p)
        if not fn_ptr:
            raise RuntimeError('Function "{}" not found.'.format(py_name))

        func = (FUNCTYPE(return_type, *args))(fn_ptr.value)
        result.append((py_name, func))
    return result

# Vulkan declarations & utils ###############################################

VkInstance = c_size_t

VkInstanceCreateFlags = c_uint

def VK_MAKE_VERSION(major, minor, patch):
    return (major<<22) | (minor<<12) | patch
VK_API_VERSION_1_0 = VK_MAKE_VERSION(1,0,0)
VK_API_VERSION_1_1 = VK_MAKE_VERSION(1,1,0)

VkStructureType = c_uint
VK_STRUCTURE_TYPE_APPLICATION_INFO = 0
VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO = 1

VkResult = c_int
VK_SUCCESS = 0

def define_struct(name, *args):
    return type(name, (Structure,), {'_fields_': args})

VkApplicationInfo = define_struct('VkApplicationInfo',
    ('sType', VkStructureType),
    ('pNext', c_void_p),
    ('pApplicationName', c_char_p),
    ('applicationVersion', c_uint),
    ('pEngineName', c_char_p),
    ('engineVersion', c_uint),
    ('apiVersion', c_uint),
)

VkInstanceCreateInfo = define_struct('VkInstanceCreateInfo',
    ('sType', VkStructureType),
    ('pNext', c_void_p),
    ('flags', VkInstanceCreateFlags),
    ('pApplicationInfo', POINTER(VkApplicationInfo)),
    ('enabledLayerCount', c_uint),
    ('ppEnabledLayerNames', POINTER(c_char_p)),
    ('enabledExtensionCount', c_uint),
    ('ppEnabledExtensionNames', POINTER(c_char_p)),
)

LoaderFunctions = (
    (b'vkCreateInstance', VkResult, POINTER(VkInstanceCreateInfo), c_void_p, POINTER(VkInstance),),
)

InstanceFunctions = (
    (b'vkDestroyInstance', None, VkInstance, c_void_p),
)

vkGetInstanceProcAddr = vk.vkGetInstanceProcAddr
vkGetInstanceProcAddr.restype = FUNCTYPE(None,)
vkGetInstanceProcAddr.argtypes = (VkInstance, c_char_p,)

def VkResultStr(result):
    if   (result == 0):   return 'VK_SUCCESS'
    elif (result == 1):   return 'VK_NOT_READY'
    elif (result == 2):   return 'VK_TIMEOUT'
    elif (result == 3):   return 'VK_EVENT_SET'
    elif (result == 4):   return 'VK_EVENT_RESET'
    elif (result == 5):   return 'VK_INCOMPLETE'
    elif (result == -1):  return 'VK_ERROR_OUT_OF_HOST_MEMORY'
    elif (result == -2):  return 'VK_ERROR_OUT_OF_DEVICE_MEMORY'
    elif (result == -3):  return 'VK_ERROR_INITIALIZATION_FAILED'
    elif (result == -4):  return 'VK_ERROR_DEVICE_LOST'
    elif (result == -5):  return 'VK_ERROR_MEMORY_MAP_FAILED'
    elif (result == -6):  return 'VK_ERROR_LAYER_NOT_PRESENT'
    elif (result == -7):  return 'VK_ERROR_EXTENSION_NOT_PRESENT'
    elif (result == -8):  return 'VK_ERROR_FEATURE_NOT_PRESENT'
    elif (result == -9):  return 'VK_ERROR_INCOMPATIBLE_DRIVER'
    elif (result == -10): return 'VK_ERROR_TOO_MANY_OBJECTS'
    elif (result == -11): return 'VK_ERROR_FORMAT_NOT_SUPPORTED'
    elif (result == -12): return 'VK_ERROR_FRAGMENTED_POOL'
    else: return 'unknown'

# main() ####################################################################

if len(sys.argv) != 4:
    raise RuntimeError('usage: {} <major> <minor> <patch>'.format(sys.argv[0]))

# get desired Vulkan API version from the commandline.
major = int(sys.argv[1])
minor = int(sys.argv[2])
patch = int(sys.argv[3])

app_info = VkApplicationInfo(
    sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    pNext              = None,
    pApplicationName   = b'CreateInstanceVersion.py',
    applicationVersion = VK_MAKE_VERSION(1,0,0),
    pEngineName        = None,
    engineVersion      = 0,
    apiVersion         = VK_MAKE_VERSION(major,minor,patch)
)

create_info = VkInstanceCreateInfo(
    sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    pNext                   = None,
    flags                   = 0,
    pApplicationInfo        = pointer(app_info),
    enabledLayerCount       = 0,
    ppEnabledLayerNames     = None,
    enabledExtensionCount   = 0,
    ppEnabledExtensionNames = None
)

inst = VkInstance(0)

f=locals()
for name, func in GetFunctions(inst, LoaderFunctions, vkGetInstanceProcAddr):
    f[name] = func

result = vkCreateInstance(byref(create_info), None, byref(inst))
print(result,VkResultStr(result))

if result != VK_SUCCESS:
    raise RuntimeError('vkCreateInstance() failed')

f = locals()
for name, func in GetFunctions(inst, InstanceFunctions, vkGetInstanceProcAddr):
    f[name] = func

vkDestroyInstance(inst, None)

# vim: set sw=4 ts=8 et ic ai:
