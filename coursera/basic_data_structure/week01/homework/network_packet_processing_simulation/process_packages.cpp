#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        last_finish_time_(0),
        finish_time_()
    {}

    Response Process(const Request &request) {
        while(finish_time_.empty() == false && finish_time_.front() <= request.arrival_time) {
            finish_time_.pop();
        }

        if (finish_time_.size() == size_) {
            return Response(true, request.arrival_time);
        }
        Response res(false, last_finish_time_);
        if (last_finish_time_ < request.arrival_time) {
            res.start_time = request.arrival_time;
            last_finish_time_ = request.arrival_time + request.process_time;
        } else {
            last_finish_time_ += request.process_time;
        }
        finish_time_.push(last_finish_time_);
        return res;
    }
private:
    int size_;
    int last_finish_time_;
    std::queue <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
