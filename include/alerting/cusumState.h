#pragma once

struct CusumState
 {
    double baseline;   
    double s_pos = 0;  
    double s_neg = 0;  
    bool initialized = false;
};