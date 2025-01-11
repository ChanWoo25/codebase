#include <cpr/cpr.h>
#include <fmt/core.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iostream>

DEFINE_string(command, "get", "'get', 'post', 'put', 'patch', 'delete'");
DEFINE_int32(id, 0, "The id");
DEFINE_int32(userid, 0, "The id of users");

void Test00() {
  cpr::Response r = cpr::Get(
      cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
      cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
      cpr::Parameters{{"anon", "true"}, {"key", "value"}});
  auto status_code = r.status_code;       // 200
  auto header = r.header["content-type"]; // application/json; charset=utf-8
  auto text = r.text;                     // JSON text string

  fmt::println("status_code: {}", status_code);
  fmt::println("header: {}", header);
  fmt::println("text: {}", text);
}

void Get() {
  const auto &id = FLAGS_id;
  const auto &userid = FLAGS_userid;

  if (userid > 0) {
    cpr::Response r = cpr::Get(
        cpr::Url{"https://jsonplaceholder.typicode.com/posts"},
        cpr::Parameters{
            {"userId", std::to_string(userid)}}, // userId=1인 데이터만 요청
        cpr::Timeout{2000});                     // Timeout 설정: 2000ms == 2s
    if (r.status_code == 0) {
      std::cerr << "Timout out occurs!" << std::endl;
    }
    std::cout << "Status Code: " << r.status_code << "\n"; // HTTP response code
    std::cout << "Response Text: " << r.text << "\n";      // Response body
  }

  if (id > 0) {
    cpr::Response r =
        cpr::Get(cpr::Url{fmt::format(
                     "https://jsonplaceholder.typicode.com/posts/{}", id)},
                 cpr::Timeout{2000}); // Timeout 설정: 2000ms == 2s
    if (r.status_code == 0) {
      std::cerr << "Timout out occurs!" << std::endl;
    }
    std::cout << "Status Code: " << r.status_code << "\n";
    std::cout << "Response Text: " << r.text << "\n";
  }
}

void Post() {
  // Perform a POST request
  cpr::Response post_response = cpr::Post(
      cpr::Url{"https://jsonplaceholder.typicode.com/posts"},
      cpr::Payload{{"title", "foo"}, {"body", "bar"}, {"userId", "1"}});
  std::cout << "POST Response: " << post_response.text << "\n";
}

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (FLAGS_command == "get") {
    Get();
  } else if (FLAGS_command == "post") {
    Post();
  }

  return EXIT_SUCCESS;
}
