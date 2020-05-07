#!/bin/bash

export DEVICE_NAME="esp8266"
export REGION_NAME="europe-west1"
export REGISTRY_NAME="iot-registry"

# Generate an Eliptic Curve (EC) ES256 private / public key pair
openssl ecparam -genkey -name prime256v1 -noout -out ec_private.pem
openssl ec -in ec_private.pem -pubout -out ec_public.pem

# Create a new Cloud IOT device
gcloud iot devices create $DEVICE_NAME \
  --region=$REGION_NAME \
  --registry=$REGISTRY_NAME \
  --public-key="path=./ec_public.pem,type=es256"
