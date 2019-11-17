
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>


static const char *pagefilename = "page.out";
char *url = "https://www.google.com/";

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

int download_page()
{

 
printf(" \n \n ");
printf("..........................................\n ");
printf("          ooooo     ooo ooooooooo.   ooooo     \n ");   
printf("          `888'     `8' `888   `Y88. `888'      \n ");  
printf(" .ooooo.   888       8   888   .d88'  888        \n "); 
printf("d88' `'Y8  888       8   888ooo88P'   888        \n "); 
printf("888        888       8   888`88b.     888        \n "); 
printf("888   .o8  `88.    .8'   888  `88b.   888       o \n ");
printf("`Y8bod8P'    `YbodP'    o888o  o888o o888ooooood8 \n ");
printf("..........................................\n ");
printf(" \n \n ");


  CURL *curl_handle;
  FILE *pagefile;
  curl_global_init(CURL_GLOBAL_ALL);
  curl_handle = curl_easy_init();
  curl_easy_setopt(curl_handle, CURLOPT_URL, url);
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
  pagefile = fopen(pagefilename, "wb");
  if(pagefile) {
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);
    curl_easy_perform(curl_handle);
    fclose(pagefile);
  }
  curl_easy_cleanup(curl_handle);
  curl_global_cleanup();
  return 0;
}

int main()
{

download_page();

printf("\n \n \n");
printf("The URL  %s \n", url);
printf("Has been downloaded and written to %s \n ", pagefilename);


return 0;
}