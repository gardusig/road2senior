FROM python:3.9

WORKDIR /app

COPY /client /app
COPY /resources /app/resources

RUN pip install grpcio
RUN pip install grpcio-tools

CMD ["python", "main.py"]
