//
// Created by Matthew Hambrecht on 11/14/23.
//

#include "Body.h"

Body::Body() {
    _loaded = false;
};

Body::Body(Mat & body) {
    _body = body;
    _loaded = true;
};

void Body::showBody() const { // Display single body for debugging
    if (!_loaded) {
        return;
    }
    if (!_body.empty()) {
        imshow("Debug (Body)", _body);
        waitKey(0);
        destroyAllWindows();
    }
}