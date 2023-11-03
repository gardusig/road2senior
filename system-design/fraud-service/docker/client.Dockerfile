FROM python:3.9

WORKDIR /app

COPY /server /app

RUN pip install grpcio-tools

CMD ["python", "main.py"]
