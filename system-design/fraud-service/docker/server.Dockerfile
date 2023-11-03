FROM ruby:3.0

WORKDIR /app
COPY /server ./
COPY /proto/generated/ruby ./generated

RUN bundle install

RUN cat Gemfile
RUN cat Gemfile.lock

EXPOSE 50051

CMD ["ruby", "main.rb"]
