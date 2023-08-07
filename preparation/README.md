- [Summary](#summary)
- [Coding interview](#coding-interview)
- [Behavioral interview](#behavioral-interview)
- [System design interview](#system-design-interview)
- [Ask at the end](#ask-at-the-end)

# Summary

The interview process generally consists of a few interviews, the goal is to cover each type by documenting a few tricks to prepare and get an offer.

## Coding interview

This interview generally takes up to an hour, and you are generally expected to solve a few problem(s) using algorithms and data structures.

Few guides:

- Iterate through some examples to check if you understood the problem and try to find corner cases ASAP
- Ask clarifying questions
- Be honest if you already saw the question before
- Think about distinct solutions and their trade-offs, using time and space complexity to compare them
- Write good quality code, easily readable and efficient, not something that just works
- Test the code by running it against small input/output scenarios and explain what happens at each step. Actually creating each variable and explaining their value changes over execution is just fine.

## Behavioral interview

This interview generally takes up to an hour, and you are generally expected to cover a few of your past experiences. The key point is not to feel ashamed of mistakes, they are quite useful when you have learned a lesson. As you make more distinct mistakes, the better you tend to become.

Few guides:

- Don't be very technical
- Add STAR method explanation link

## System design interview

This interview generally takes up to an hour, and you are generally expected to draw a few things that can be read as a computer system. It does not have to be perfect, otherwise you would be eligible to replace a bunch of people :)

I have defined some kind of algorithm, still ongoing process. Let's use Twitter as an example:

1. Understand the system by asking the dumbest questions until you can answer the question below
   - What is actually the goal? As a user, I would like to...
     - Login
     - Post my brilliant 256 character thought(s)
     - Read other people's brilliant 256 character thought(s)
     - Subscribe other people
     - Be subscribed by other people
     - Read from a feed
     - Receive notifications
1. Translate previous questions into real data, which is like a bunch of databases
   - User db should have like
     - Id (primary key if sql)
     - Name
     - Password
     - Favorite color
   - Tweet db should have like
     - Id (primary key if sql)
     - Brilliant 256 character thoughts
   - Subscription db TODO
1. Understand the expected traffic by asking more dumb questions. Don't forget to guess a few answers to keep the conversation fluid
   - How many users?
   - How many requests per day?
   - Write/read ratio?
   - Budget/Timeline (startups does not allow to evaluate many alternatives)
   - Auth layer/system
   - Metrics collection
   - Log system
   - Data formats (monoliths are easier to handle, better consistency)
     - protocol buffers
     - json
     - xml
     - smoke signal
   - Communication (monoliths are easier to handle, better consistency)
     - HTTP
     - gRPC
   - Availability. What is more important, consistency or speed?
     - Considering medical and bank stuff, consistency is very important
     - Brilliant 256 character thoughts? Nah, as quick as possible, no one will die if one disappear
   - What are the corner cases?
     - Famous people should be very interesting to have astronomically more subscribers than avg
     - Creative people write a ton of brilliant 256 character thoughts every day
     - Curious people read a ton of brilliant 256 character thoughts every day

Few guides:

- Understand the project idea and look at it as a user
- Ask clarifying questions with more details and remove ambiguity
- Define which data should be stored
- Think about how you would organize their storage
- Understand data flow and define APIs to access them
- Draw a few boxes with a general flow from the UI request to the response
- Estimate resource usage and investigate where is the bottleneck
- Discussions may touch:
  - Security
  - Deployment
  - Automation
  - Maintenance
  - Metrics collection
    - Alarms

## Ask at the end

By the end of each interview, you are expected to have around 5 minutes to ask a few questions to the interviewer. It's an opportunity to clarify if you actually likes the company and maybe show interest through an unexpected curiosity.

Few guides:

- On-call
  - What is the rotation period? (i.e. Every two weeks)
  - How much time is expected to spend away from standard tasks?
  - Is the team looking for avoiding more tickets?
- Remote work
  - What are the rules?
  - Does employees receive tool reimbursement?
- Promotion
  - Are there enough projects to support next level experience?
  - What are expectations? And what should be improved to get promoted?
  - How the promotion process looks like?
