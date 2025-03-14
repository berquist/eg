ARG USERID=1001

FROM debian:sid-20250224-slim

ARG USERID
ARG USERNAME=builder
RUN useradd --uid ${USERID} --user-group -s /bin/bash ${USERNAME}
USER ${USERNAME}
RUN echo "USERID=${USERID}"
RUN --mount=type=cache,target=/tmp/hello,uid=${USERID},gid=${USERID} \
    stat /tmp/hello
