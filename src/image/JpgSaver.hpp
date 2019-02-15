//
//  JpgSaver.hpp
//  firstSketch
//
//  Created by Egon Firman on 15/02/19.
//

#ifndef JpgSaver_hpp
#define JpgSaver_hpp

#include <stdio.h>

class JpgSaver {
    
public:
    void save(char * filename, unsigned char *data, int width, int height);

};


#endif /* JpgSaver_hpp */
