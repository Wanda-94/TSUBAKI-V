
message("compiler vulkan current path ${CMAKE_CURRENT_LIST_DIR}")

set(VULKAN_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/Include/")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(VULKAN_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/Lib/vulkan-1.lib")
    set(VULKAN_LINK_DIRS "${CMAKE_CURRENT_LIST_DIR}/Lib/")

elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(VULKAN_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/Lib/vulkan-1.lib")
    set(VULKAN_LINK_DIRS "${CMAKE_CURRENT_LIST_DIR}/Lib/")
endif()

target_include_directories(TSUBAKI-V PRIVATE ${VULKAN_INCLUDE_DIRS} )

target_link_directories(TSUBAKI-V PRIVATE ${VULKAN_LINK_DIRS} )

target_link_libraries(TSUBAKI-V PRIVATE ${VULKAN_LIBRARIES} )
