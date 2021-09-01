# fetch 3rd party libraries
include(FetchContent)

FetchContent_Declare(
  googletest
  URL               https://github.com/google/googletest/archive/release-1.8.1.tar.gz
  URL_MD5           2e6fbeb6a91310a16efe181886c59596

)

FetchContent_Declare(
  googlebenchmark
  URL               https://github.com/google/benchmark/archive/refs/tags/v1.5.5.tar.gz
  URL_MD5           6f852815d48db788f5bb87e2e561dc5e

)

add_subdirectory(googletest)
add_subdirectory(googlebenchmark)
