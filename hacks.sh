#!/bin/bash

curl -X POST http://ecen192.byu.edu/control_device \
  -H "Content-Type: multipart/form-data; boundary=---------------------------41330616352355792544644421330" \
  -d '-----------------------------41330616352355792544644421330
Content-Disposition: form-data; name="control_type"

play_song
-----------------------------41330616352355792544644421330
Content-Disposition: form-data; name="ip_address"

10.37.220.155
-----------------------------41330616352355792544644421330
Content-Disposition: form-data; name="password"

hehehe
-----------------------------41330616352355792544644421330
Content-Disposition: form-data; name="new_password"

hehehe
-----------------------------41330616352355792544644421330--'
