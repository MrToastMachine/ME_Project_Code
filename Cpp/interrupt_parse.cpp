#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

typedef struct objects_detected {
    std::vector<int> object_starts{};
    std::vector<int> object_sizes{};
} objects_detected;

typedef struct sensor_data {
    char sensor_id;
    objects_detected sensor_A_objs;
    objects_detected sensor_B_objs;
    objects_detected sensor_C_objs;
} sensor_data;

sensor_data myData;

// Initialize with actual values
vector<int> interrupt_times_all{27, 52, 77, 103, 128, 146, 153, 178, 195, 202, 227, 252, 277, 302, 327, 351, 376, 401, 425, 442, 450, 467, 475, 500, 524, 549, 574, 599, 624, 648, 673, 698, 723, 747, 772, 797, 821, 845, 870, 895, 919, 943, 968, 992, 1016, 1037, 1040, 9754, 9759, 9786, 9812, 9828, 9837, 9854, 9863, 9888, 9913, 9938, 9963, 9989, 10014, 10039, 10064, 10088, 10105, 10113, 10138, 10163, 10187, 10212, 10237, 10261, 10286, 10311, 10336, 10360, 10385, 10401, 10410, 10435, 10460, 10485, 10510, 10534, 10559, 10584, 10600, 10609, 10633, 10658, 10683, 10708, 10733, 10751, 10758, 10776, 10782, 10807, 10831, 10852, 10856, 19763, 19791, 19810, 19817, 19842, 19868, 19893, 19918, 19943, 19968, 19993, 20018, 20043, 20068, 20092, 20117, 20146, 20166, 20191, 20213, 20215};

vector<int> sensor_A_start_dists;
vector<int> sensor_A_lengths;

using namespace std;

void parseInterruptsToObjects(vector<int> interrupt_times, objects_detected& obj_info){
    int current_object_start = interrupt_times[0];

    // min num interrupts to classify as object
    const int MIN_COUNT_FOR_OBJECT = 15;
    // max time allowed between interrupts to be part of same object
    const int MAX_DELTA = 30;

    int count = 1;

    cout<<"interrupt_times.size() = "<<interrupt_times.size()<< endl;

    for (int i = 1; i < interrupt_times.size(); i++){
        if (interrupt_times[i] < 1200){
            continue;
        }


        int delta = interrupt_times[i] - interrupt_times[i-1];

        if (delta < MAX_DELTA){
            count++;
        }
        else {
            if (count >= MIN_COUNT_FOR_OBJECT){
                obj_info.object_starts.push_back(current_object_start);
                obj_info.object_sizes.push_back(interrupt_times[i-1] - current_object_start);
                // myData.obj_times.push_back(current_object_start);
                // myData.obj_sizes.push_back(interrupt_times[i-1] - current_object_start);
                // sensor_A_start_dists.push_back(current_object_start);
                // sensor_A_lengths.push_back(interrupt_times[i-1] - current_object_start);
            }
            current_object_start = interrupt_times[i];
            count = 1;
        }

        
    }


    if (count >= MIN_COUNT_FOR_OBJECT) {
        obj_info.object_starts.push_back(current_object_start);
        obj_info.object_sizes.push_back(interrupt_times[interrupt_times.size()-1] - current_object_start);
        // myData.obj_times.push_back(current_object_start);
        // myData.obj_sizes.push_back(interrupt_times[interrupt_times.size()-1] - current_object_start);
        // sensor_A_start_dists.push_back(current_object_start);
        // sensor_A_lengths.push_back(interrupt_times[interrupt_times.size()-1] - current_object_start);
    }
}

int main(int argc, char const *argv[]) {

    cout<<"[Before parsing]"<<endl;
    cout<<"Object Data..."<<endl;

    for (int i = 0; i < myData.sensor_A_objs.object_starts.size(); i++){
        cout << myData.sensor_A_objs.object_starts[i] << ", " << myData.sensor_A_objs.object_sizes[i] << endl;
    }
    cout<<endl;

    parseInterruptsToObjects(interrupt_times_all, myData.sensor_A_objs);

    cout<<"[After parsing]"<<endl;
    cout<<"Object Data..."<<endl;

    for (int i = 0; i < myData.sensor_A_objs.object_starts.size(); i++){
        cout << myData.sensor_A_objs.object_starts[i] << ", " << myData.sensor_A_objs.object_sizes[i] << endl;
    }
    cout<<endl;

    //CLEARING

    myData.sensor_A_objs.object_starts.clear();
    myData.sensor_A_objs.object_sizes.clear();

    cout<<"[After Clearing]"<<endl;
    cout<<"Object Data..."<<endl;

    for (int i = 0; i < myData.sensor_A_objs.object_starts.size(); i++){
        cout << myData.sensor_A_objs.object_starts[i] << ", " << myData.sensor_A_objs.object_sizes[i] << endl;
    }
    cout<<endl;

    cout<<"Done..."<<endl;

    return 0;
}
