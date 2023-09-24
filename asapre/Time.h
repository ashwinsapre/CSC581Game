class Time{
public:
    int64_t start_time = 0;
    int64_t current_time = 0;
    int64_t tic = 1;

    Time(){}

    void next_time(){
        current_time += tic;
    }
};