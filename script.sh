#!/bin/bash
echo "port" $(lsof -t -i:8000) "was killed"
kill $(lsof -t -i:8000)