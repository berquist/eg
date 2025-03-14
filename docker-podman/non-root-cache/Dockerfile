ARG USERID=1001

FROM debian:sid-20250224-slim

ARG USERID

RUN --mount=type=cache,target=/tmp/hello,uid=${USERID},gid=${USERID} \
    stat /tmp/hello
