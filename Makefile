.PHONY: help
.DEFAULT_GOAL := help

DOCKER=$(shell which docker)
REPOSITORY?=dendebaiano/suricato-nodered
VERSION?=2.0.0

image: ## build the docker image from Dockerfile
	$(DOCKER) build --no-cache -t ${REPOSITORY}:${VERSION} \
        --build-arg VERSION=${VERSION} \
        --build-arg VCS_REF=`git rev-parse --short HEAD` \
        --build-arg BUILD_DATE=`date -u +"%Y-%m-%dT%H:%M:%SZ"` . && \
        $(DOCKER) push ${REPOSITORY}:${VERSION}

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'