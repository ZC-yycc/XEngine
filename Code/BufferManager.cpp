#include "BufferManager.h"
#include "XEngine.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

BufferManager *BufferManager::pBuffer_manager_obj_ = new BufferManager();

BufferManager::BufferManager() 
{
}
BufferManager::~BufferManager()
{
}
