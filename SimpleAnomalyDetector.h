

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include "minCircle.h"

struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	Circle c = Circle(Point(0,0),0);
	float threshold;
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    protected: vector<correlatedFeatures> cf;
public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts)=0;
	virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;

	vector<correlatedFeatures> getNormalModel(){
		return cf;
	}
    //float threshold (Line l, Point* arr, int size);
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */
