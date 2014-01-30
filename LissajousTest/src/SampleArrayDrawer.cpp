#include "SampleArrayDrawer.h"

SampleArrayDrawer::SampleArrayDrawer()
{
}

SampleArrayDrawer::~SampleArrayDrawer()
{
}

void SampleArrayDrawer::setRectangle(const ofRectangle &rectangle)
{
    mRectangle.set(rectangle);
}

void SampleArrayDrawer::drawWave(float *array)
{
    ofBeginShape();
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofVertex(((float)i / (float)BUFFER_SIZE) * mRectangle.width + mRectangle.x,
                (array[i] * (mRectangle.height / 2)) + (mRectangle.height / 2) + mRectangle.y);
    }
    ofEndShape(false);
}