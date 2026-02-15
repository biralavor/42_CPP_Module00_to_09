set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(BitcoinExchange_lib
	src/BitcoinExchange.cpp
	src/utils.cpp
)

target_include_directories(BitcoinExchange_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(bitcoin_exchange
	src/main.cpp
)

target_link_libraries(bitcoin_exchange PRIVATE
	BitcoinExchange_lib
)
