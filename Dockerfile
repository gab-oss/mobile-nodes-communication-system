FROM ubuntu

COPY . /app

WORKDIR /app

EXPOSE 3000

CMD ["./TIN", "IPV4", "255.255.255.255", "3000", "0"]
