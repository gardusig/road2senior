FROM ruby:3.0

WORKDIR /app
COPY /server ./

RUN bundle install

EXPOSE 50051

CMD ["ruby", "main.rb"]
