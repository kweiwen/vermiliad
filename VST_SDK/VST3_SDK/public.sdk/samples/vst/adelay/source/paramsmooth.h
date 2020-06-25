//
//  paramsmooth.h
//  adelay
//
//  Created by kweiwen tseng on 2020/6/25.
//

#ifndef paramsmooth_h
#define paramsmooth_h

class ParamSmooth
{
public:
    ParamSmooth(float smoothingTimeInMs, float samplingRate)
    {
        const float c_twoPi = 6.283185307179586476925286766559f;
        
        a = exp(-c_twoPi / (smoothingTimeInMs * 0.001f * samplingRate));
        b = 1.0f - a;
        z = 0.0f;
    }
    
    ~ParamSmooth()
    {
        
    }
    
    inline float process(float in)
    {
        z = (in * b) + (z * a);
        return z;
    }
    
private:
    float a;
    float b;
    float z;
};


#endif /* paramsmooth_h */
