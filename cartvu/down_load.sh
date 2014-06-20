#!/bin/sh
echo "open  $1   21
      user  $2   $3
      binary
      get   $4
      close
      bye"| ftp -i -in >> /etc/error_download
