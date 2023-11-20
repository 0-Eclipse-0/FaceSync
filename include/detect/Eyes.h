//
// Created by Matthew Hambrecht on 11/19/23.
//

#ifndef FACESYNC_EYES_H
#define FACESYNC_EYES_H
#include "Eye.h"
#include "Feature.h"
#include <vector>

class Eyes {
public:
    Eyes();
    Eyes(Mat & frame, std::string & cascadeFile);
    void getEyes();
    bool getLoaded() const;
    std::vector <Eye> returnEyes();
private:
    Mat * _frame;
    CascadeClassifier _cascade;
    bool _loaded;
    std::vector <Eye> _eyes;
};


#endif //FACESYNC_EYES_H
