#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <cmath>

using namespace std;

//Loads the Experiment Measurements from a text file into a vector of doubles
vector<double> load_dataset_into_vector(string filename) {
    vector<double> word_list;
    ifstream file_handle(filename.c_str());
    if (file_handle.good()) {
        string word_string;
        while (true) {
            file_handle >> word_string;
            word_list.push_back(atof(word_string.c_str()));
            if (file_handle.eof())
                break;
        }
    }
    return word_list;
}

double mean(const vector<double> &value_list) {
    //TODO This function takes as input a vector of values, calculate and return the mean of these values
    double sum = 0;
    for (int i = 0; i < value_list.size(); i++) {
        sum += value_list[i];
    }
    return sum / value_list.size();
}

double median(vector<double> value_list) {
    //TODO This function takes as input a vector of values and you need to calculate and return the median of these values
    sort(value_list.begin(), value_list.end());
    if (value_list.size() % 2 == 0) {
        return (value_list[value_list.size() / 2] + value_list[value_list.size() / 2 - 1]) / 2;
    } else {
        return value_list[value_list.size() / 2];
    }
}

//Find and return the Minimum value that was found in a vector
double minimum(const vector<double> &value_list) {
    //TODO Find and return the minimum value that was found in a vector of values
    double min_val = value_list[0];
    for (int i = 1; i < value_list.size(); i++) {
        min_val = min(min_val,value_list[i]);
    }
    return min_val;
}

//Find and return the Maximum value that was found in a vector
double maximum(const vector<double> &value_list) {
    //TODO Find and return the maximum value that was found in a vector of values
    double max_val = value_list[0];
    for (int i = 1; i < value_list.size(); i++) {
        max_val = max(max_val,value_list[i]);
    }
    return max_val;
}

vector<int> histogram(vector<double> value_list,double min_bound,double max_bound,int n_buckets) {
    //TODO Generate and return the histogram of the provided values between the min_bound and max_bound
    vector<int> histogram_list(n_buckets,0);
    double range = max_bound - min_bound;
    for (int i = 0; i < n_buckets; i++) {
        int bucket_id = round((value_list[i]-min_bound)/range*(n_buckets-1));
        histogram_list[bucket_id]++;
    }
    for (int i = 0; i < n_buckets; i++) {
        cout << "hist[" << i << "]=" << histogram_list[i] << endl;
    }
    return histogram_list;
}

double mode(vector<double> value_list,int n_buckets) {
    //TODO Find Minimum and Maximum bound
    double min_bound = minimum(value_list);
    double max_bound = maximum(value_list);
    //TODO Build Histogram
    vector<int> histogram_list = histogram(value_list, min_bound, max_bound, n_buckets);
    //TODO Find Maximum Peak/Bucket
    int max_peak_index = 0;
    double range = max_bound-min_bound;
    for (int i = 1; i < n_buckets; i++) {
        if (histogram_list[i] > histogram_list[max_peak_index]) {
            max_peak_index = i;
        }
    }
    //TODO Convert max bucket position to the mode value and return
    return double(max_peak_index/n_buckets-1) * range+min_bound;
}

int main() {
    double groundtruth_lightspeed=3.3368744961031980650362805697393e-9,
           measurement_distance=7443.73;
    //Load Experiment Measurements
    vector<double> value_list=load_dataset_into_vector("dataset.txt");

    //TODO Convert speed of light measurements to meters per second
    vector<double> speed_of_light_list;
    for (int i = 0; i < value_list.size(); i++) {
        value_list[i] =value_list[i]/measurement_distance;
    }
    //TODO Calculate Mean, Median and Mode
    double mean_speed_of_light = mean(value_list);
    double median_speed_of_light = median(value_list);
    double mode_speed_of_light = mode(value_list, 10);
    //TODO Calculate Estimation Error and Display Estimation and Error results
    cout << "Mean Estimate:  = " << mean_speed_of_light << " Error = " << abs(mean_speed_of_light - groundtruth_lightspeed) << endl;
    cout << "Median Estimate = " << median_speed_of_light << " Error = " << abs(median_speed_of_light - groundtruth_lightspeed) << endl;
    cout << "Mode Estimate   = " << mode_speed_of_light << " Error = " << abs(mode_speed_of_light - groundtruth_lightspeed) << endl;
    return 0;
}

