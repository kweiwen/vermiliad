//
//  circularbuffer.h
//  adelay
//
//  Created by kweiwen tseng on 2020/6/25.
//

#ifndef circularbuffer_h
#define circularbuffer_h

#include <math.h>

template <typename T>
class CircularBuffer
{
public:
    CircularBuffer()
    {
        _writeIndex = 0;
        _bufferLength = 0;
        _wrapMask = 0;
    };
    
    ~CircularBuffer()
    {
        delete[] _buffer;
        delete[] _polynomials;
    };
    
    struct SampleSet
    {
        T x, y;
    };
    
    void createCircularBuffer(unsigned int _bufferLength);
    void createPolynomials(unsigned int nthroots);
    void flushBuffer();
    void writeBuffer(T input);
    
    T readBuffer(float delayInSamples);
    float readBuffer(float delayInFractionalSamples, bool interpolate);
    
    static float doLinearInterpolation(float y1, float y2, float fractional_X);
    static float doLargrangeInterpolation(SampleSet polynomials[], float delayInFractionalSamples, int n);
    
private:
    T* _buffer = nullptr;
    SampleSet* _polynomials = nullptr;
    unsigned int _writeIndex;
    unsigned int _bufferLength;
    unsigned int _wrapMask;
    unsigned int _nthRoots;
};

template <typename T>
void CircularBuffer<T>::createCircularBuffer(unsigned int bufferLength)
{
    // reset the to top
    _writeIndex = 0;
    // init buffer length as power of 2
    _bufferLength = (unsigned int)(pow(2, ceil(logf(bufferLength) / logf(2))));
    // warp mask as (buffer length - 1) for binary &= calculation
    _wrapMask = _bufferLength - 1;
    
    // create new buffer, type as template type, array size as buffer length, {} makes the element as null which is equal 0
    _buffer = new T[_bufferLength]{};
}

template<typename T>
inline void CircularBuffer<T>::createPolynomials(unsigned int nthRoots)
{
    _nthRoots = nthRoots;
    _polynomials = new SampleSet[_nthRoots];
}

template <typename T>
void CircularBuffer<T>::flushBuffer()
{
    for (int i = 0; i < _bufferLength; i++)
    {
        _buffer[i] = 0;
    }
}

template <typename T>
void CircularBuffer<T>::writeBuffer(T input)
{
    _buffer[_writeIndex++] = input;
    _writeIndex &= _wrapMask;
}

template<typename T>
T CircularBuffer<T>::readBuffer(float delayInSamples)
{
    int readIndex = _writeIndex - (int)delayInSamples;
    readIndex &= _wrapMask;
    return _buffer[readIndex];
}

template<typename T>
inline float CircularBuffer<T>::readBuffer(float delayInFractionalSamples, bool interpolate)
{
    if (interpolate == false)
    {
        T y1 = readBuffer(delayInFractionalSamples);
        T y2 = readBuffer(delayInFractionalSamples + 1);
        float fraction = delayInFractionalSamples - (int)delayInFractionalSamples;
        return doLinearInterpolation(y1, y2, fraction);
    }
    else
    {
        for (int i = 0; i < sizeof(_polynomials); i++)
        {
            _polynomials[i].x = T(delayInFractionalSamples - 2 + i);
            _polynomials[i].y = readBuffer(delayInFractionalSamples - 2 + i);
        };
        return doLargrangeInterpolation(_polynomials, delayInFractionalSamples, sizeof(_polynomials));
    }
}

template<typename T>
inline float CircularBuffer<T>::doLinearInterpolation(float y1, float y2, float fractional_X)
{
    if (fractional_X >= 1.0) return y2;
    return fractional_X * y2 + (1 - fractional_X)*y1;
}

template<typename T>
inline float CircularBuffer<T>::doLargrangeInterpolation(SampleSet polynomials[], float delayInFractionalSamples, int n)
{
    float result = 0;
    for (int i = 0; i < n; i++)
    {
        float term = polynomials[i].y;
        for (int j = 0; j < n; j++)
        {
            if (j != i)
                term = term * (delayInFractionalSamples - polynomials[j].x) / float(polynomials[i].x - polynomials[j].x);
        }
        result += term;
    }
    return result;
}

#endif /* circularbuffer_h */
