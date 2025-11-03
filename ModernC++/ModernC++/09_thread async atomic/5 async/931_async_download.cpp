// 예제 : 스레드 사용 코드

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
// ----------------------------------- added
#include <queue>
#include <future>
// -----------------------------------------
using namespace std;
using namespace std::chrono;

int download_music(int music_id)
{
	// use music id (identify music)
	// ...
	if (music_id == 1)		this_thread::sleep_for(1s);
	else if (music_id == 2)	this_thread::sleep_for(2s);
	else					this_thread::sleep_for(3s);

	return 42; // return music data
}

int main()
{
	auto time_for_animation = steady_clock::now();
	auto download_timing = steady_clock::now() + 1s;
	auto process_end_timing = steady_clock::now() + 5s;

	vector<int> downloaded_musics;

	// ----------------------------------- added
	queue<future<int>> download_tasks;					// future 목록
	// -----------------------------------------

	// app main loop
	while (1)
	{
		auto curr_time_point = steady_clock::now();

		// for background animation (ui thread) --------------------------
		if (curr_time_point - time_for_animation > 100ms)
		{
			cout << '.';
			time_for_animation = curr_time_point;
		}

		// proces download start ------------------------------------------
		if (download_timing < curr_time_point)
		{
			// --------------------- modified
			download_tasks.push(async(launch::async, download_music, 1));
			download_tasks.push(async(launch::async, download_music, 2));
			download_tasks.push(async(launch::async, download_music, 3));

			// never download again!
			download_timing = curr_time_point + 100h;
		}

		// added ----------------------------------------------------------
		if (!download_tasks.empty())
		{
			auto& f = download_tasks.front();
			// 일정 시간만큼 값이 전달되기 기다리다, timout이 되면 block 상태가 해제
			if (f.valid() && future_status::ready == f.wait_for(0ms))
			{
				//download complete
				int music_data = f.get();
				downloaded_musics.push_back(music_data);
				cout << music_data;
				download_tasks.pop();
			}
		}

		// end -------------------------------------------------------------
		if (process_end_timing < curr_time_point)
		{
			if (download_tasks.empty())
			{
				cout << '\n';
				break;
			}
		}
	}

	cout << "my music_list: ";
	for (const auto& music : downloaded_musics)
	{
		cout << music << ' ';
	}
	cout << endl;
}
