FROM python:3.9

WORKDIR /app

COPY /client /app

RUN pip install grpcio-tools

CMD ["python", "main.py"]
