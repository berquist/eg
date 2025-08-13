ARG USERID=1001

FROM debian:sid-20250224-slim@sha256:a326760b6408687b0898a57d64a5dd195a768fc435c406df44e9a45b86cb21a1

ARG USERID
ARG USERNAME=builder
RUN useradd --uid ${USERID} --user-group -s /bin/bash ${USERNAME}
USER ${USERNAME}
RUN echo "USERID=${USERID}"
RUN --mount=type=cache,target=/tmp/hello,uid=${USERID},gid=${USERID} \
    stat /tmp/hello
