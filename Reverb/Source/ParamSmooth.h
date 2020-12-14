//
//  ParaSmooth.h
//
//  Created by kweiwen tseng on 2020/6/25.
//

#ifndef ParamSmooth_h
#define ParamSmooth_h

const float c_twoPi = 6.283185307179586476925286766559f;

class ParamSmooth
{
public:
    ParamSmooth(float smoothingTimeInMs, float samplingRate)
    {
        // smoothingTimeInMs
        // samplingRate
        
        a = exp(-c_twoPi / (smoothingTimeInMs * 0.001f * samplingRate));
        b = 1.0f - a;
        z = 0.0f;
    }
    
    ~ParamSmooth()
    {
        
    }
    
    inline float process(float input)
    {
        z = (input * b) + (z * a);
        return z;
    }
    
private:
    float a;
    float b;
    float z;
};


#endif /* ParamSmooth_h */
