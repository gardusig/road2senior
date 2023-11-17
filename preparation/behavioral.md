# Summary

- Don't be very technical
- Try using STAR method whenever possible

## STAR method

The STAR method is a structured way of answering behavioral interview questions. It stands for Situation, Task, Action, and Result.

- **Situation**: Describe the context of the situation. This could be a work-related situation, a volunteer experience, or even a personal situation. Be sure to provide enough detail so that the interviewer can understand the situation.
- **Task**: What was your specific goal or responsibility in this situation?
- **Action**: What steps did you take to achieve your goal? Be as specific as possible and highlight the skills and abilities you used.
- **Result**: What was the outcome of your actions? Did you achieve your goal? If so, how? If not, what did you learn from the experience?

## Story creation guidance

- Add a title summarizing the story into an impactful message
  - Easy to remember and may catch interviewer attention
    - Like a sensationalist news headline
- Evaluate consistency between stories
  - One must not invalidate another, they should complement each other
    - Beware of writing style, may be easier to remember when following a pattern
    - Do like Sherlock Holmes - be consistent and methodical
- People like numbers, why not make stories sound a bit more palpable?
  - Just add fucking details everywhere
    - Awesome improvement you have made at service X... But, by how much percent?
    - Astonishingly processing time reduction at service Y... By how much, hum?
    - Do like Gabriela Prioli - seasoning with granular refined data and its source
- Remove unnecessary details
  - Still figuring out what is not recommended to speak at an interview
- Tailor each story towards a positive feeling by the end
  - Do like He Man - conclude them with a lessons learned at the end

## From remote startup developer to nightclub owner

### Leadership Principles

- Hire and Develop the Best
- Customer Obsession
- Ownership
- Invent and Simplify
- Think Big
- Bias for Action

### Entrepreneurial Success

#### Situation

- Got to know about a potential opportunity to invest money, bar/nightclub
  - Kinda cheap initial investment for the moment
- It was already an odd place, but still required improvements
  - Worked but not optimally
- I wanted it to become an unique place at the city
  - Something they never saw before

#### Task

- Refactor appearance
- Find the first team members
- Manage finances
- Resolve government bureaucracy
- Evaluate ways for easy maintenance
- Discover different ways to use the remaining space

#### Action

- Find the most important person
  - The manager
- Make refactor happen
  - Paint
  - Remove walls
  - Add walls
  - Add forces against fire
  - Decorate
  - Final touches with art
  - Moved things around
- Deeply understand finances
  - Otherwise, it does not make sense to hold up the company
  - Given that profit margin was not the major goal, just crossing self maintenance was just enough
- Play with art and colors
  - Each ambient had a unique feeling
    - Colors must resemble it
    - Paintings as well

#### Result

- Profitable nightclub
  - Between SDE1 and SDE2 compensation
- Virtually working on automatic
  - Had a few maintenance tasks with very low time consumption
- Good enough fame for 1st attempt
  - Crossed 5k followers after around 6 months at my hand
- Sold for around 1 year of net income
- Learned many remaining pieces for team management or so

All of that while working at a Silicon Valley startup job :)

## Why have I left Orkes?

### Leadership Principles

- Think Big
- Bias for Action
- Frugality

### Pursuit of a better suitable environment

I was initially happy with the remote contract at the startup. The compensation was much higher than I would have received as a full-time employee in Brazil, and I had the freedom to work from anywhere. However, I soon realized that the company culture was not a good fit for me. They were looking for people who would follow a command-and-control management style, and I am more of a creative thinker who likes to challenge the status quo.

The company culture tone changed after the first year. It became more stressful and demanding, with the management turning to be less supportive. I felt like I was no longer being heard or valued. I also saw how the team was being treated, and I didn't want to be a part of that.

I was disappointed that the management team stopped appearing and recommended to avoid code reviews. I felt like they didn't care about the team or the work we were doing. This made me feel like I was on my own, and it made it difficult to get the support I needed.

I am still proud of the work I did at the startup. I contributed to many open source projects, and I believe that my work has had a positive impact on the community. I learned that it's important to be clear about my expectations and to find a company culture that is a good fit for me.

After the contract ended, I took some vacation after a long time without one. I also made a good deal selling my company, which allowed me to be free to study and get back on the programming track again.

## Why have I left Amazon to join a startup?

#### Leadership Principles

- Learn and Be Curious
- Think Big
- Frugality

### Desire for more challenging and fulfilling work

I joined Amazon as a software engineer on the amazon.com.br fba team. I was excited about the opportunity to work for a large and innovative company, but I quickly realized that the role was not a good fit for me.

The projects I was working on were not very challenging or interesting. I was basically adding more layers to existing services in order to be compliant with Brazilian laws. I also felt like I was constantly working on tech debt. I improved the resilience score of a service, but it was then transferred to another team and I was given a new task that was very similar.

In addition, I was not happy with the compensation and benefits. As a Brazilian employee, I was paid in BRL and had to pay high taxes. When I was offered a remote position at a startup in Silicon Valley, I jumped at the chance.

The new position paid me in USD and I had much lower taxes. I was also able to work remotely, which gave me the freedom to live anywhere I wanted. I was much happier with the projects I got to work on and felt like I made a real impact.

Leaving Amazon was clearly the right choice. Even got an equivalent offer from AWS to relocate to Canada, but that's another disappointing story of many suboptimal decisions.

## How I upscaled Amazon FBA invoice services just enough?

### Leadership Principles

- Customer Obsession
- Invent and Simplify
- Insist on the Highest Standards
- Bias for Action

### Ability to prepare a system for high-demand periods like Black Friday

As one of the biggest e-commerce companies, things do not work as simple as waiting for a load to break systems and then upscale them. Users might go to the competitor purchase what they're looking for if it does not work out at their 1st attempt. Preparation is key to situations like these, and sometimes paying a bit more for being overcautious is just fine.

I had previously worked at understanding the microservices my team was responsible for. It consisted at updating their deployment pipelines to add a new step with tests relevant to higher load. Which means, trying to load test every new merged code before actually deploying it to user facing hosts.

It not only helped the resilience score of the team, but it showed a few important data - like the most transactions per second (TPS) that a server could handle before starting to fail requests.

With that in mind, the neighbor team had some secret data containing their projected amount of clients expected to use our system during the next peak season.

If you evaluate metrics, each service has a few APIs that are much more used than others. Considering the previous TPS and the projected amount of users, you can connect this with the most used APIs.

So you basically know how many requests are expected for this service at the peak. Considering how many requests a single host can handle before failing them. Just divide the amount of forecasted requests per the TPS and then you have the amount of hosts you must have.

We rounded up values to make sure we weren't being too pretentious and it's done. Worked pretty fine during the BF 2021. After that just downscale again and watch the results.

## How I enabled the largest client for Orkes by creating an SDK

### Leadership Principles

- Customer Obsession
- Ownership
- Learn and Be Curious

### Adaptability and initiative in learning new technologies to quickly create solutions

- Twilio wanted to use the product, but not only asked but set a requirement - to have Go SDK
- Previously to me, only java developers had support
- It was the first time I touched Go code
- Ended up creating a client capable of transforming Go functions into Netflix Conductor workflow task workers
  - It contained a few wrappers for server side HTTP communication through its APIs
    - All generated by using swagger codegen
  - Stored auth token
  - Polled for tasks in batches, starting a separate go routine for each execution
  - Managed amount of available resources, keeping concurrent operations as much to a pre defined limit
- People got happy with results and a new customer was being managed from then on

## How have I managed all SDKs while at Orkes?

### Leadership Principles

- Customer Obsession
- Ownership
- Insist on the Highest Standards

### Commitment to maintain and improve multiple software while automating as much as possible

- Created Python and Go SDKs
- Improved Java SDK
- Helped to launch C#, JS and Clojure SDKs
- Created integration tests aiming for 100% coverage of relevant code, like most used APIs
- Automated build, test and release through CI/CD at GitHub actions
- Virtually each SDK had automation for:
  - generating HTTP server side API code through swagger codegen
  - run tests automatically on pull request events
  - build package and publish to pkg manager on new release events
- Handle GitHub issues and package versioning
  - Broke compatibility
  - Fixed them overnight

## How have I dealt with manager disagreement?

### Leadership Principles:

- Customer Obsession
- Invent and Simplify

### Make informed decisions and communicate effectively

- I had added batch polling feature for a few SDKs
  - Which increased performance by ~20% due to latency
- My manager asked to do the same for Python SDK
- I thought it was a bad idea and disagreed with him
  - It's not because I know how to do something that we should actually do
  - Python has GIL, which makes parallel processing a bit more complex and less efficient
  - This was by far the hardest feature to add for an SDK without breaking compatibility and keep our stability standards
  - Python is not the most efficient programming language, users looking for better performance probably aren't using this tool
- I suggested making a few quick fix solution, like relying at multithreading
  - Which could improve I/O tasks
  - Still does not run in parallel for CPU tasks
- By the end it was an agreement that it's a nice to have but does not bring much value
  - Given a startup context, time management is the most important measure to keep an eye at
  - Adding a new complex feature with not much return value is a very bad choice
- Comparing to other priorities on the user request roadmap, it was the right path to be followed at the moment
