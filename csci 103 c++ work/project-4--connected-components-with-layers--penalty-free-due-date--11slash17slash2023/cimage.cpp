#include "component.h"
#include "cimage.h"
#include "bmplib.h"
#include <deque>
#include <iomanip>
#include <iostream>
#include <cmath>
// You shouldn't need other #include's - Ask permission before adding

using namespace std;

// TO DO: Complete this function
CImage::CImage(const char* bmp_filename)
{
    //  Note: readRGBBMP dynamically allocates a 3D array
    //    (i.e. array of pointers to pointers (1 per row/height) where each
    //    point to an array of pointers (1 per col/width) where each
    //    point to an array of 3 unsigned char (uint8_t) pixels [R,G,B values])

    // ================================================
    // TO DO: call readRGBBMP to initialize img_, h_, and w_;
    img_ = readRGBBMP(bmp_filename, h_, w_);


    // Leave this check
    if(img_ == NULL) {
        throw std::logic_error("Could not read input file");
    }

    // Set the background RGB color using the upper-left pixel
    for(int i=0; i < 3; i++) {
        bgColor_[i] = img_[0][0][i];
    }

    // ======== This value should work - do not alter it =======
    // RGB "distance" threshold to continue a BFS from neighboring pixels
    bfsBgrdThresh_ = 60;

    // ================================================
    // TO DO: Initialize the vector of vectors of labels to -1
    labels_.resize(h_);
    for (int i = 0; i < h_; i++) {
        for (int j = 0; j < w_; j++) {
            labels_[i].push_back(-1);
        }
    }


    // ================================================
    // TO DO: Initialize any other data members
    components_ = vector<Component>();

}

// TO DO: Complete this function
CImage::~CImage()
{
    // Add code here if necessary
    deallocateImage(img_);

}

// Complete - Do not alter
bool CImage::isCloseToBground(uint8_t p1[3], double within) {
    // Computes "RGB" (3D Cartesian distance)
    double dist = sqrt( pow(p1[0]-bgColor_[0],2) +
                        pow(p1[1]-bgColor_[1],2) +
                        pow(p1[2]-bgColor_[2],2) );
    return dist <= within;
}

// TO DO: Complete this function
size_t CImage::findComponents()
{
    int num_bfs_calls = 0;
    for (int i = 0; i < h_; i++) {
        for (int j = 0; j < w_; j++) {
            if ((labels_[i][j] == -1) && (!isCloseToBground(img_[i][j], bfsBgrdThresh_))) {
                Component comp = bfsComponent(i, j, num_bfs_calls);
                components_.push_back(comp);
                num_bfs_calls++;
            }
        }
    }
    return num_bfs_calls;
    //pushing into components vector
    // if u find a pixel thats not the background color
    // incrmeneting for # of times we call this bfs


}

// Complete - Do not alter
void CImage::printComponents() const
{
    cout << "Height and width of image: " << h_ << "," << w_ << endl;
    cout << setw(4) << "Ord" << setw(4) << "Lbl" << setw(6) << "ULRow" << setw(6) << "ULCol" << setw(4) << "Ht." << setw(4) << "Wi." << endl;
    for(unsigned int i = 0; i < components_.size(); i++) {
        const Component& c = components_[i];
        cout << setw(4) << i << setw(4) << c.label << setw(6) << c.ulNew.row << setw(6) << c.ulNew.col
             << setw(4) << c.height << setw(4) << c.width << endl;
    }

}


// TODO: Complete this function
int CImage::getComponentIndex(int mylabel) const
{
    for (unsigned int i = 0; i <components_.size(); i++) {
        if (components_[i].label == mylabel) {
            return i;
        }
    }
    return -1;
}


// Nearly complete - TO DO:
//   Add checks to ensure the new location still keeps
//   the entire component in the legal image boundaries
void CImage::translate(int mylabel, int nr, int nc)
{
    // Get the index of specified component
    int cid = getComponentIndex(mylabel);
    if(cid < 0) {
        return;
    }
    int h = components_[cid].height;
    int w = components_[cid].width;

    // ==========================================================
    // ADD CODE TO CHECK IF THE COMPONENT WILL STILL BE IN BOUNDS
    // IF NOT:  JUST RETURN.
    Location nl(nr,nc);
    if ((nl.row < 0) || (nl.row + h > h_) || (nl.col < 0) || (nl.col + w > w_)) {
        return;
        // check if component isn;t in bounds
    }
    // component will be in bounds if we update its location
   // components_[cid].ulNew = nl;


    // ==========================================================

    // If we reach here we assume the component will still be in bounds
    // so we update its location.
    //Location nl(nr, nc);
    components_[cid].ulNew = nl;
}

// TO DO: Complete this function
void CImage::forward(int mylabel, int delta)
{
    int cid = getComponentIndex(mylabel);
    if(cid < 0 || delta <= 0) {
        return;
    }
    // Add your code here
    int new_idx = min(cid + delta, (int)components_.size()-1);

    if (new_idx == cid) {
        return;
    }
    Component temp = components_[cid];
    for (int i = cid; i < new_idx; i++) {
        components_[i] = components_[i+1];
    }
    components_[new_idx] = temp;

}

// TO DO: Complete this function
void CImage::backward(int mylabel, int delta)
{
    int cid = getComponentIndex(mylabel);
    if(cid < 0 || delta <= 0) {
        return;
    }
    // Add your code here
    int new_idx = max(cid-delta, 0);
    if (new_idx == cid) {
        return;
    }
    Component temp = components_[cid];
    for (int i = cid; i > new_idx; i--) {
        components_[i] = components_[i-1];
    }
    components_[new_idx] = temp;

}

// TODO: complete this function
void CImage::save(const char* filename)
{
    // Create another image filled in with the background color
    uint8_t*** out = newImage(bgColor_);

    // Add your code here
    for (size_t k = 0; k < components_.size(); k++) {
        Component c = components_[k];
        for (int i = 0; i < c.height; i++)  {
            for (int j = 0; j < c.width; j++) {
               int oldRow = c.ulOrig.row + i;
               int oldCol = c.ulOrig.col + j;
               int newRow = c.ulNew.row + i;
               int newCol = c.ulNew.col + j;
               if ((newRow >= 0) && (newRow < h_) && (newCol >=0) && (newCol < w_) && 
               (labels_[oldRow][oldCol] == c.label)) {
                    for (int z = 0; z < 3; z++) {
                        out[newRow][newCol][z] = img_[oldRow][oldCol][z];
                    }  
                }
            }
        }
        // check bounds
    }

    writeRGBBMP(filename, out, h_, w_);
    // Add any other code you need after this
    //deallocate
    deallocateImage(out);


    //writeRGBBMP(filename, out, h_, w_);
    // Add any other code you need after this
    
}

// Complete - Do not alter - Creates a blank image with the background color
uint8_t*** CImage::newImage(uint8_t bground[3]) const
{
    uint8_t*** img = new uint8_t**[h_];
    for(int r=0; r < h_; r++) {
        img[r] = new uint8_t*[w_];
        for(int c = 0; c < w_; c++) {
            img[r][c] = new uint8_t[3];
            img[r][c][0] = bground[0];
            img[r][c][1] = bground[1];
            img[r][c][2] = bground[2];
        }
    }
    return img;
}

// To be completed
void CImage::deallocateImage(uint8_t*** img) const
{
    // Add your code here
    for (int i = 0; i < h_; i++) {
        for (int j = 0; j < w_; j++) {
            delete[] img[i][j];
        }
        delete[] img[i];
    }
    delete [] img;
}

// TODO: Complete the following function or delete this if
//       you do not wish to use it.
Component CImage::bfsComponent(int pr, int pc, int mylabel)
{
    // Arrays to help produce neighbors easily in a loop
    // by encoding the **change** to the current location.
    // Goes in order N, NW, W, SW, S, SE, E, NE
    int neighbor_row[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int neighbor_col[8] = {0, -1, -1, -1, 0, 1, 1, 1};
    
    deque<Location> q;
    q.push_back(Location(pr,pc));
    labels_[pr][pc] = mylabel;
    int min_row = q.front().row;
    int max_row = q.front().row;
    int min_col = q.front().col;
    int max_col = q.front().col;

    while (!q.empty()) {
        Location curr = q.front();
        if (curr.row <= min_row) {
                        min_row = curr.row;
                    }
                    if (curr.row > max_row) {
                        max_row = curr.row;
                    }
                    if (curr.col <= min_col) {
                        min_col = curr.col;
                    }
                    if (curr.col > max_col) {
                        max_col = curr.col;
                    }
        q.pop_front(); // extract curr location
        // check neighbors
        for (int i=0; i<8; i++) {
            int nr = curr.row+neighbor_row[i];
            int nc = curr.col+neighbor_col[i];
            if ((nr >= 0) && (nr < h_) && (nc >=0) && (nc < w_) && (labels_[nr][nc] == -1) && (!isCloseToBground(img_[nr][nc], bfsBgrdThresh_))) {
              // >= 0 < height
                //if ((labels_[nr][nc] == -1) && (!isCloseToBground(img_[nr][nc], bfsBgrdThresh_))) {
                    labels_[nr][nc] = mylabel; 
                    q.push_back(Location(nr,nc));
            }
        }  
    }   
    Location location;
    int height = max_row - min_row + 1;
    int width = max_col - min_col + 1;
    location.row = min_row;
    location.col = min_col;
    Component component(location, height, width, mylabel);
    return component;


}

// Complete - Debugging function to save a new image
void CImage::labelToRGB(const char* filename)
{
    //multiple ways to do this -- this is one way
    vector<uint8_t[3]> colors(components_.size());
    for(unsigned int i=0; i<components_.size(); i++) {
        colors[i][0] = rand() % 256;
        colors[i][1] = rand() % 256;
        colors[i][2] = rand() % 256;
    }

    for(int i=0; i<h_; i++) {
        for(int j=0; j<w_; j++) {
            int mylabel = labels_[i][j];
            if(mylabel >= 0) {
                img_[i][j][0] =  colors[mylabel][0];
                img_[i][j][1] =  colors[mylabel][1];
                img_[i][j][2] =  colors[mylabel][2];
            } else {
                img_[i][j][0] = 0;
                img_[i][j][1] = 0;
                img_[i][j][2] = 0;
            }
        }
    }
    writeRGBBMP(filename, img_, h_, w_);
}

// Complete - Do not alter
const Component& CImage::getComponent(size_t i) const
{
    if(i >= components_.size()) {
        throw std::out_of_range("Index to getComponent is out of range");
    }
    return components_[i];
}

// Complete - Do not alter
size_t CImage::numComponents() const
{
    return components_.size();
}

// Complete - Do not alter
void CImage::drawBoundingBoxesAndSave(const char* filename)
{
    for(size_t i=0; i < components_.size(); i++){
        Location ul = components_[i].ulOrig;
        int h = components_[i].height;
        int w = components_[i].width;
        for(int i = ul.row; i < ul.row + h; i++){
            for(int k = 0; k < 3; k++){
                img_[i][ul.col][k] = 255-bgColor_[k];
                img_[i][ul.col+w-1][k] = 255-bgColor_[k];

            }
            // cout << "bb " << i << " " << ul.col << " and " << i << " " << ul.col+w-1 << endl; 
        }
        for(int j = ul.col; j < ul.col + w ; j++){
            for(int k = 0; k < 3; k++){
                img_[ul.row][j][k] = 255-bgColor_[k];
                img_[ul.row+h-1][j][k] = 255-bgColor_[k];

            }
            // cout << "bb2 " << ul.row << " " << j << " and " << ul.row+h-1 << " " << j << endl; 
        }
    }
    writeRGBBMP(filename, img_, h_, w_);
}

// Add other (helper) function definitions here

