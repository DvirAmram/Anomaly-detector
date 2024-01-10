
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}
float threshold (Line l, Point** arr, int size){
    float max = 0;
    for (int i = 0; i < size; ++i) {
        if(dev(*arr[i],l) > max){
            max = dev(*arr[i],l);
        }
    }
    return max;
}

void HybridAnomalyDetector::learnNormal(const TimeSeries& ts){
    int num = ts.getKeys().size();
    string v1;
    string v2;
    float* x;
    float* y;
    for (int i = 0; i < num;i++) {
        float m = 0;
        int c = -1;
        float p;
        vector<float> v1 = ts.getMap().find(ts.getKeys()[i])->second;
        //from vector to arr
        x = v1.data();
        for (int j = i+1; j < num;j++){
            vector<float> v2 = ts.getMap().find(ts.getKeys()[j])->second;
            //from vector to arr
            y = v2.data();
            // checks which vector is the most correlative to i vector
            p = fabsf( pearson(x, y, ts.getMap().find(ts.getKeys()[j])->second.size()));
            if(fabs(p) > m){
                m = p;
                c = j;
            }
        }
        if (c != -1){
            //builds an arr of points
            Point** arr = new Point* [ts.getMap().find(ts.getKeys()[c])->second.size()];
            for (int j = 0; j < ts.getMap().find(ts.getKeys()[c])->second.size() ; ++j) {
                arr[j] = new Point (ts.getMap().find(ts.getKeys()[i])->second[j], ts.getMap().find(ts.getKeys()[c])->second[j]);
            }
            //initializes the cof
            correlatedFeatures cof;
            cof.feature1 = ts.getKeys().at(i);
            cof.feature2 = ts.getKeys().at(c);
            cof.corrlation = m;
            if (m>=0.9) {
                cof.lin_reg = linear_reg(arr, ts.getMap().find(ts.getKeys()[c])->second.size());
                cof.threshold = (1.2) * ::threshold(cof.lin_reg, arr, ts.getMap().find(ts.getKeys()[c])->second.size());
                this->cf.push_back(cof);
            } else{
                if (m>0.5){
                    cof.c = findMinCircle(arr, ts.getMap().find(ts.getKeys()[c])->second.size());
                    cof.lin_reg = Line(0, 0);
                    cof.threshold = (1.1) * cof.c.radius;
                    this->cf.push_back(cof);
                }
            }
        }
    }
}
/**
 * @param ts the data structure
 * @return vector of the AnomalyReport that has time and a decription of the alarm.
 */
vector<AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> vectorReports;
    vector<float> v1;
    vector<float> v2;
    for(int i = 0; i < cf.size(); i++) {
        v1 = ts.getMap().find(cf[i].feature1)->second;
        v2 = ts.getMap().find(cf[i].feature2)->second;
        for (int j = 0; j < v1.size(); j++) {
            Point *point = new Point(v1[j], v2[j]);
            if (cf[i].corrlation >= 0.9) {
                float deviation = dev(*point, cf[i].lin_reg);
                if (deviation >= cf[i].threshold) {
                    string description = cf[i].feature1 + "-" + cf[i].feature2;
                    AnomalyReport *report = new AnomalyReport(description, j + 1);
                    vectorReports.push_back(*report);
                }
            } else {
                if (cf[i].corrlation > 0.5) {
                    float deviation = dist(*point, cf[i].c.center);
                    if (deviation >= cf[i].threshold) {
                        string description = cf[i].feature1 + "-" + cf[i].feature2;
                        AnomalyReport *report = new AnomalyReport(description, j + 1);
                        vectorReports.push_back(*report);
                    }
                }
            }
        }
    }
    return vectorReports;
}