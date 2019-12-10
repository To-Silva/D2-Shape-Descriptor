#include <set> 
#include <vector>
#include <UniformPointSampling.h>

using namespace std;

vector<int> computeD2(vector<vec3> samples) {
	multiset <double, less <double> > distsSet;
	vector<double> dists;
	vector<int> D2histogram;
	int normalizationValue = 10,stepNum=100;
	double max = 0;

	//compute distances from sample list
	for (int j = 0; j < samples.size(); j++) {
		for (int i = j + 1; i < samples.size(); i++) {
			vec3 v1 = samples[i];
			vec3 v2 = samples[j];
			double dist = glm::distance(v1, v2);
			if (dist > max) max = dist;
			dists.push_back(dist);
		}
	}
	//normalize
	for (int i = 0; i < dists.size(); i++) { dists[i] /= max; dists[i] *= normalizationValue; distsSet.insert(dists[i]); }

	multiset <double, less <double> >::iterator it = distsSet.begin();

	//compute frequency for each histogram step
	double step = normalizationValue / (double)stepNum;
	for (double i = step; i <= normalizationValue; i+=step) {
		int frequency = 0;
		for (; i > *it; it++) frequency++;
		D2histogram.push_back(frequency);
	}
	return D2histogram;
}