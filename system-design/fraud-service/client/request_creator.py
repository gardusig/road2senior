from google.protobuf.timestamp_pb2 import Timestamp
from proto.generated import transaction_pb2
from typing import Dict, List
import csv
import datetime


def get_timestamp_from_str(timestamp: str) -> Timestamp:
    datetime_obj = datetime.datetime.fromisoformat(timestamp)
    timestamp_message = Timestamp()
    timestamp_message.FromDatetime(datetime_obj)
    return timestamp_message


column_name_to_request_param = {
    "transaction_id": ("transactionId", str),
    "merchant_id": ("merchantId", str),
    "user_id": ("userId", str),
    "card_number": ("cardNumber", str),
    "transaction_date": ("transactionDate", get_timestamp_from_str),
    "transaction_amount": ("transactionAmount", float),
    "device_id": ("deviceId", str),
    "has_cbk": ("hasCbk", lambda x: x == "TRUE")
}


def generate_request(column_name_to_row_index: Dict[str, int], csv_row: List[str]) -> transaction_pb2.IsTransactionValidRequest:
    request_data = {}
    for column_name, (attr_name, conversion_func) in column_name_to_request_param.items():
        index = column_name_to_row_index[column_name]
        value = csv_row[index]
        if conversion_func:
            value = conversion_func(value)
        request_data[attr_name] = value
    return transaction_pb2.IsTransactionValidRequest(**request_data)


def get_requests_from_file(filepath: str = "resources/transactional-sample.csv") -> List[transaction_pb2.IsTransactionValidRequest]:
    requests = []
    with open(filepath, 'r') as csvfile:
        csvreader = csv.reader(csvfile)
        header = next(csvreader)
        column_name_to_row_index = {}
        for index in range(len(header)):
            column_name_to_row_index[header[index]] = index
        for csv_row in csvreader:
            request = generate_request(column_name_to_row_index, csv_row)
            if request:
                requests.append(request)
    return requests
