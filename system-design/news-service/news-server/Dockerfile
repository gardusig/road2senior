FROM gradle:jdk15 AS build
COPY --chown=gradle:gradle ./build.gradle /home/gradle/build.gradle
COPY --chown=gradle:gradle ./src/ /home/gradle/src/
WORKDIR /home/gradle/
RUN gradle build

FROM openjdk:15
EXPOSE ${SERVER_PORT}
RUN mkdir ./app/
COPY --from=build /home/gradle/build/libs/*.jar ./app/spring-boot-application.jar
ENTRYPOINT ["java", "-jar", "./app/spring-boot-application.jar"]
