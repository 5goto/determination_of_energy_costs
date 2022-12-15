#include <memory>
#include <cstring>
#include <algorithm>

static auto my_get_data(std::size_t size)
{
	auto v = std::make_unique<int[]>(size);
	std::fill_n(v.get(), size, 5);
	return v;
}

auto data_buffer = my_get_data(1ull << 28);

