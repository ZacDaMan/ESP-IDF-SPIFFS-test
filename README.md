# ESP-IDF-SPIFFS-test
This repository is a small PlatformIO project to demonstrate a bug with PlatformIO's partition table parser.
As of repository creation date, building this project will result in the Filesystem Image being flashed to 0x207000, while ESP-IDF expects it to be at 0x210000, causing a mounting error.
This is because PlatformIO fails to account for an automatic alignment of any `app` type partitions. Once the issue is fixed, the image should instead be flashed to 0x210000
