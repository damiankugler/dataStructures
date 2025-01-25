import json
import os
import requests

artist = 'MilfDoggoVa'

file_path = f"response_{artist}.json"

with open(file_path, "r", encoding="utf-8") as file:
    data = json.load(file)

count = 0
links_list = []
title_list = []

save_dir = f"E:/Thumb Drive Backup/+1/New folder (2)/Upload/Audio/{artist}/"

if not os.path.exists(save_dir):
    os.makedirs(save_dir)

url = 'https://n3.kemono.su/data'

for mp3 in data:
    count += 1

    if 'name' in mp3['file']:
        title = mp3['file']['name']
        if title.endswith(".mp3") or title.endswith(".flac") or title.endswith(".wav"):
            title_list.append(mp3['file']['name'])
    if 'path' in mp3['file']:
            links_list.append(url + mp3['file']['path'])


# for link, title in zip(links_list,title_list):
#     print(link)
#     print(title)

for link, title in zip(links_list,title_list):
    file_name = title
    # file_name = f"{title.strip('!?.')}.mp3"
    save_path = os.path.join(save_dir, file_name)
    res = requests.get(link)

    if res.status_code == 200:
        with open(save_path, "wb") as file:
            file.write(res.content)
        print(f"The file '{title}' was downloaded to {save_path}")
    else:
        print(f"Failed to download {title}")

print("Finished the whole json.")