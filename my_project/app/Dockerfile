FROM gcc:latest  
WORKDIR /app  
COPY ./app/ /app  
RUN 
RUN g++ -o app -O2 /app/main.cpp  
CMD ["./app"]
