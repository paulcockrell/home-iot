#!/bin/bash

export PROJECT_ID="home-iot-20200429 "
export PUBSUB_TOPIC="iot-topic"
export PUBSUB_SUBSCRIPTION="iot-subscription"
export REGISTRY_NAME="iot-registry"
export DEVICE_NAME="esp8266"

# Choose your region: https://cloud.google.com/compute/docs/regions-zones/
# Valid cloud regions are {asia-east1,europe-west1,us-central1}
export REGION_NAME="europe-west1"

# Authorize gcloud to access the Cloud Platform with Google user credentials
gcloud auth login

# Create a new project
gcloud projects create $PROJECT_ID

# Set default project
gcloud config set project $PROJECT_ID

# Enable Cloud Pub/Sub
gcloud services enable pubsub.googleapis.com

# Enable billing (required for Cloud IoT. You can also use the `gcloud beta billing` CLI)
open https://console.cloud.google.com/iot/api?project=$PROJECT_ID

# Enable Cloud IoT
gcloud services enable cloudiot.googleapis.com

# Give permission to Cloud IoT Core to publish messages on Cloud Pub/Sub
gcloud projects add-iam-policy-binding $PROJECT_ID --member=serviceAccount:cloud-iot@system.gserviceaccount.com --role=roles/pubsub.publisher

# Create Cloud Pub/Sub topic for event notifications
gcloud pubsub topics create $PUBSUB_TOPIC

# Create Cloud Pub/Sub subscription
gcloud pubsub subscriptions create $PUBSUB_SUBSCRIPTION --topic $PUBSUB_TOPIC

# Create Cloud IoT registry specifying Cloud Pub/Sub topic name
gcloud iot registries create $REGISTRY_NAME \
  --region=$REGION_NAME \
  --event-notification-config=topic=$PUBSUB_TOPIC \
  --enable-mqtt-config --enable-http-config