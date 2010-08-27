#include "Core/Utils.hpp"

void Utils::setDimension(string& d)
{
    boost::to_lower(d);
    if (d == "2d")
    {
        mDimension = "2D";
        #define TWO_DIMENSIONS
    }
    else if (d == "3d")
    {
        mDimension = "3D";
        #define THREE_DIMENSIONS
    }
}

ptime Utils::getCurrentTime() const
{
    return microsec_clock::local_time();
}

const string Utils::getMediaPath() const
{
	return mMediaPath;
}

void Utils::setMediaPath(const string &path)
{
	mMediaPath = path;
}

const string Utils::getDimension() const
{
    return mDimension;
}

void Utils::writeTimestamp()
{
    mTimeStamp = getCurrentTime();
}

string Utils::getTimeDifference()
{
	// If we don't call writeTimestamp before this function
	if (mTimeStamp.is_not_a_date_time()) LOG("You are trying to get time difference but you have to call writeTimestamp first!");

	time_duration result = getCurrentTime() - mTimeStamp;
	mTimeStamp = ptime(not_a_date_time);

	return to_simple_string(result);
}

void Utils::createPlane(Ogre::Mesh *newMesh)
{
    using namespace Ogre;

    SubMesh* sub = newMesh->createSubMesh();
    float vertices[32] = {
            -100, -100, 0,	// pos
            0,0,1,              // normal
            0,1,		// texcoord
            100, -100, 0,
            0,0,1,
            1,1,
            100,  100, 0,
            0,0,1,
            1,0,
            -100,  100, 0 ,
            0,0,1,
            0,0
    };
    newMesh->sharedVertexData = OGRE_NEW VertexData();
    newMesh->sharedVertexData->vertexCount = 4;
    VertexDeclaration* decl = newMesh->sharedVertexData->vertexDeclaration;
    VertexBufferBinding* bind = newMesh->sharedVertexData->vertexBufferBinding;

    size_t offset = 0;
    decl->addElement(0, offset, VET_FLOAT3, VES_POSITION);
    offset += VertexElement::getTypeSize(VET_FLOAT3);
    decl->addElement(0, offset, VET_FLOAT3, VES_NORMAL);
    offset += VertexElement::getTypeSize(VET_FLOAT3);
    decl->addElement(0, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES, 0);
    offset += VertexElement::getTypeSize(VET_FLOAT2);

    HardwareVertexBufferSharedPtr vbuf =
            HardwareBufferManager::getSingleton().createVertexBuffer(
            offset, 4, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
    bind->setBinding(0, vbuf);

    vbuf->writeData(0, vbuf->getSizeInBytes(), vertices, true);

    sub->useSharedVertices = true;
    HardwareIndexBufferSharedPtr ibuf = HardwareBufferManager::getSingleton().
            createIndexBuffer(
            HardwareIndexBuffer::IT_16BIT,
            6,
            HardwareBuffer::HBU_STATIC_WRITE_ONLY);

    unsigned short faces[6] = {0,1,2,
            0,2,3 };
    sub->indexData->indexBuffer = ibuf;
    sub->indexData->indexCount = 6;
    sub->indexData->indexStart =0;
    ibuf->writeData(0, ibuf->getSizeInBytes(), faces, true);

    newMesh->_setBounds(AxisAlignedBox(-100,-100,0,100,100,0), true);
    newMesh->_setBoundingSphereRadius(Math::Sqrt(100*100+100*100));
}

void Utils::createSphere(Ogre::Mesh *newMesh)
{
    using namespace Ogre;

    SubMesh *pSphereVertex = newMesh->createSubMesh();

    const int NUM_SEGMENTS = 16;
    const int NUM_RINGS = 16;
    const Real SPHERE_RADIUS = 50.0;

    newMesh->sharedVertexData = OGRE_NEW VertexData();
    VertexData* vertexData = newMesh->sharedVertexData;

    // define the vertex format
    VertexDeclaration* vertexDecl = vertexData->vertexDeclaration;
    size_t currOffset = 0;
    // positions
    vertexDecl->addElement(0, currOffset, VET_FLOAT3, VES_POSITION);
    currOffset += VertexElement::getTypeSize(VET_FLOAT3);
    // normals
    vertexDecl->addElement(0, currOffset, VET_FLOAT3, VES_NORMAL);
    currOffset += VertexElement::getTypeSize(VET_FLOAT3);
    // two dimensional texture coordinates
    vertexDecl->addElement(0, currOffset, VET_FLOAT2, VES_TEXTURE_COORDINATES, 0);
    currOffset += VertexElement::getTypeSize(VET_FLOAT2);

    // allocate the vertex buffer
    vertexData->vertexCount = (NUM_RINGS + 1) * (NUM_SEGMENTS+1);
    HardwareVertexBufferSharedPtr vBuf = HardwareBufferManager::getSingleton().createVertexBuffer(vertexDecl->getVertexSize(0), vertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
    VertexBufferBinding* binding = vertexData->vertexBufferBinding;
    binding->setBinding(0, vBuf);
    float* pVertex = static_cast<float*>(vBuf->lock(HardwareBuffer::HBL_DISCARD));

    // allocate index buffer
    pSphereVertex->indexData->indexCount = 6 * NUM_RINGS * (NUM_SEGMENTS + 1);
    pSphereVertex->indexData->indexBuffer = HardwareBufferManager::getSingleton().createIndexBuffer(HardwareIndexBuffer::IT_16BIT, pSphereVertex->indexData->indexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
    HardwareIndexBufferSharedPtr iBuf = pSphereVertex->indexData->indexBuffer;
    unsigned short* pIndices = static_cast<unsigned short*>(iBuf->lock(HardwareBuffer::HBL_DISCARD));

    float fDeltaRingAngle = (Math::PI / NUM_RINGS);
    float fDeltaSegAngle = (2 * Math::PI / NUM_SEGMENTS);
    unsigned short wVerticeIndex = 0 ;

    for( int ring = 0; ring <= NUM_RINGS; ring++ ) {
        float r0 = SPHERE_RADIUS * sinf (ring * fDeltaRingAngle);
        float y0 = SPHERE_RADIUS * cosf (ring * fDeltaRingAngle);

        for(int seg = 0; seg <= NUM_SEGMENTS; seg++) {
            float x0 = r0 * sinf(seg * fDeltaSegAngle);
            float z0 = r0 * cosf(seg * fDeltaSegAngle);

            *pVertex++ = x0;
            *pVertex++ = y0;
            *pVertex++ = z0;

            Vector3 vNormal = Vector3(x0, y0, z0).normalisedCopy();
            *pVertex++ = vNormal.x;
            *pVertex++ = vNormal.y;
            *pVertex++ = vNormal.z;

            *pVertex++ = (float) seg / (float) NUM_SEGMENTS;
            *pVertex++ = (float) ring / (float) NUM_RINGS;

            if (ring != NUM_RINGS) {
                *pIndices++ = wVerticeIndex + NUM_SEGMENTS + 1;
                *pIndices++ = wVerticeIndex;
                *pIndices++ = wVerticeIndex + NUM_SEGMENTS;
                *pIndices++ = wVerticeIndex + NUM_SEGMENTS + 1;
                *pIndices++ = wVerticeIndex + 1;
                *pIndices++ = wVerticeIndex;
                wVerticeIndex ++;
            }
        }; // end for seg
    } // end for ring

    vBuf->unlock();
    iBuf->unlock();

    pSphereVertex->useSharedVertices = true;

    newMesh->_setBounds( AxisAlignedBox( Vector3(-SPHERE_RADIUS, -SPHERE_RADIUS, -SPHERE_RADIUS),
            Vector3(SPHERE_RADIUS, SPHERE_RADIUS, SPHERE_RADIUS) ), false );

    newMesh->_setBoundingSphereRadius(SPHERE_RADIUS);
}
