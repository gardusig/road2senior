package com.authenticator.util;

import java.sql.Date;
import java.sql.Time;
import java.sql.Timestamp;
import java.time.LocalDate;
import java.time.ZonedDateTime;

import org.springframework.stereotype.Component;

@Component
public class TimeUtil {
    public static Timestamp getCurrentTimestamp() {
        return Timestamp.valueOf(ZonedDateTime.now().toLocalDateTime());
    }

    public static Time getCurrentTime() {
        return Time.valueOf(ZonedDateTime.now().toLocalTime());
    }

    public static Time getCurrentTimeWithAdditionalTime(final long millisecondsToAdd) {
        final Time currentTime = TimeUtil.getCurrentTime();
        final long newTime = currentTime.getTime() + millisecondsToAdd;
        return new Time(newTime);
    }

    public static long getMillisecondsFromFromDays(final long days) {
        final long minutes = days * 24 * 60;
        return TimeUtil.getMillisecondsFromMinutes(minutes);
    }

    public static long getMillisecondsFromMinutes(final long minutes) {
        return minutes * 60 * 1000;
    }

    public static Date getCurrentDate() {
        return new Date(System.currentTimeMillis());
    }

    public static Date getCurrentDateWithTime(final Time t) {
        final long currentDate = java.sql.Date.valueOf(LocalDate.now()).getTime();
        return new Date(currentDate + t.getTime());
    }
}