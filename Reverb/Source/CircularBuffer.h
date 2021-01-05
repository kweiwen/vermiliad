//
//  CircularBuffer.h
//
//  Created by kweiwen tseng on 2020/6/25.
//

#ifndef CircularBuffer_h
#define CircularBuffer_h

template <typename T>
class CircularBuffer
{

    public:
    CircularBuffer()
    {
        mWriteIndex = 0;
        mBufferLength = 0;
        mWrapMask = 0;
    };
    
    ~CircularBuffer()
    {
    };
    
    void createCircularBuffer(unsigned int input);
    void flushBuffer();
    void writeBuffer(T input);
    T readBuffer(int delayInSamples);
    T readBuffer(double delayInFractionalSamples, bool interpolate = true);
    
    static float doLinearInterpolation(float y1, float y2, float fractional_X);
    static float doHermitInterpolation(float y1, float y2, float fractional_X);
    static float doLagrangeInterpolation(float y1, float y2, float fractional_X);
    
    private:
    std::unique_ptr<T[]> mBuffer = nullptr;
    unsigned int mWriteIndex;
    unsigned int mBufferLength;
    unsigned int mWrapMask;
};

template <typename T>
void CircularBuffer<T>::createCircularBuffer(unsigned int input)
{
    // --- reset the to top
    mWriteIndex = 0;
    // --- init buffer length as power of 2
    mBufferLength = (unsigned int)(pow(2, ceil(logf(input) / logf(2))));
    // --- warp mask as (mBufferLength - 1) for binary &= calculation
    mWrapMask = mBufferLength - 1;
    // --- direct initialization object into mBufferLength size
    mBuffer.reset(new T[mBufferLength]);
    // --- clean the value inside mBuffer
    flushBuffer();
}

template <typename T>
void CircularBuffer<T>::flushBuffer()
{
    for (int i = 0; i < mBufferLength; i++)
    {
        mBuffer[i] = 0;
    }
}

template <typename T>
void CircularBuffer<T>::writeBuffer(T input)
{
    mBuffer[mWriteIndex++] = input;
    mWriteIndex &= mWrapMask;
}

template<typename T>
T CircularBuffer<T>::readBuffer(int delayInSamples)
{
    int readIndex = mWriteIndex - delayInSamples - 1;
    readIndex &= mWrapMask;
    return mBuffer[readIndex];
}

template<typename T>
// --- read an arbitrary location that includes a fractional sample
T CircularBuffer<T>::readBuffer(double delayInFractionalSamples, bool interpolate /*= true*/)
{
    // --- truncate delayInFractionalSamples and read the int part
    T y1 = readBuffer((int)delayInFractionalSamples);
    // --- if no interpolation, just return value
    if (!interpolate)
    {
        return y1;
    }
    // --- else do interpolation
    else
    {
        // --- read the sample at n+1 (one sample OLDER)
        T y2 = readBuffer((int)delayInFractionalSamples + 1);
        // --- get fractional part
        double fraction = delayInFractionalSamples - (int) delayInFractionalSamples;
        // --- do the interpolation (you could try different types here)
        return doLinearInterpolation(y1, y2, fraction);
    }
}

template<typename T>
inline float CircularBuffer<T>::doLinearInterpolation(float y1, float y2, float fractional_X)
{
    if (fractional_X >= 1.0) return y2;
    return fractional_X * y2 + (1 - fractional_X)*y1;
}

template<typename T>
inline float CircularBuffer<T>::doHermitInterpolation(float y1, float y2, float fractional_X)
{
    if (fractional_X >= 1.0) return y2;
    return fractional_X * y2 + (1 - fractional_X)*y1;
}

template<typename T>
inline float CircularBuffer<T>::doLagrangeInterpolation(float y1, float y2, float fractional_X)
{
    if (fractional_X >= 1.0) return y2;
    return fractional_X * y2 + (1 - fractional_X)*y1;
}


#endif /* CircularBuffer_h */
