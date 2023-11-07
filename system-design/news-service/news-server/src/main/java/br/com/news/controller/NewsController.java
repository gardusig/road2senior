package br.com.news.controller;

import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestHeader;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import br.com.news.provider.auth.AuthProviderApiUtil;
import br.com.news.provider.news.model.NewsArticleModel;
import br.com.news.provider.news.util.NewsProviderApiUtil;
import br.com.news.service.NewsService;
import io.swagger.v3.oas.annotations.parameters.RequestBody;

@RestController
@RequestMapping(path = "/auth")
@CrossOrigin(origins = "*")
public class NewsController {
	private final NewsService newsService;

	@Autowired
	public NewsController(final NewsService newsService) {
		this.newsService = newsService;
	}

	@GetMapping(value = "/top-headlines/query-country/{country}")
	public ResponseEntity<?> getTopHeadlinesByCountry(@RequestHeader("token") final String token,
			@RequestHeader("email") final String email, @PathVariable final String country) {
		final Optional<Integer> userID = AuthProviderApiUtil.getUserIdFromToken(email, token,
				"getTopHeadlinesByCountry");
		if (userID.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.UNAUTHORIZED);
		}
		return ResponseEntity.ok(NewsProviderApiUtil.getTopHeadlinesByCountry(country));
	}

	@GetMapping(value = "/top-headlines/query-category/{category}")
	public ResponseEntity<?> getTopHeadlinesByCategory(@RequestHeader("token") final String token,
			@RequestHeader("email") final String email, @PathVariable final String category) {
		final Optional<Integer> userID = AuthProviderApiUtil.getUserIdFromToken(email, token,
				"getTopHeadlinesByCategory");
		if (userID.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.UNAUTHORIZED);
		}
		return ResponseEntity.ok(NewsProviderApiUtil.getTopHeadlinesByCategory(category));
	}

	@GetMapping(value = "/top-headlines/query-string/{queryString}")
	public ResponseEntity<?> getTopHeadlinesByQueryString(@RequestHeader("token") final String token,
			@RequestHeader("email") final String email, @PathVariable final String queryString) {
		final Optional<Integer> userID = AuthProviderApiUtil.getUserIdFromToken(email, token,
				"getTopHeadlinesByQueryString");
		if (userID.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.UNAUTHORIZED);
		}
		return ResponseEntity.ok(NewsProviderApiUtil.getTopHeadlinesByQueryString(queryString));
	}

	@GetMapping(value = "/everything/query-string/{queryString}")
	public ResponseEntity<?> getEverythingByQueryString(@RequestHeader("token") final String token,
			@RequestHeader("email") final String email, @PathVariable final String queryString) {
		final Optional<Integer> userID = AuthProviderApiUtil.getUserIdFromToken(email, token,
				"getEverythingByQueryString");
		if (userID.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.UNAUTHORIZED);
		}
		return ResponseEntity.ok(NewsProviderApiUtil.getEverythingByQueryString(queryString));
	}

	@PostMapping(value = "/read-later/add")
	public ResponseEntity<?> addReadLater(@RequestHeader("token") final String token,
			@RequestHeader("email") final String email, @RequestBody final NewsArticleModel article) {
		final Optional<Integer> userID = AuthProviderApiUtil.getUserIdFromToken(email, token, "addReadLater");
		if (userID.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.UNAUTHORIZED);
		}
		this.newsService.addReadLater(userID.get(), article);
		return ResponseEntity.ok("entry added to user: " + userID.get());
	}

	@GetMapping(value = "/read-later/query")
	public ResponseEntity<?> queryReadLater(@RequestHeader("token") final String token,
			@RequestHeader("email") final String email) throws Exception {
		final Optional<Integer> userID = AuthProviderApiUtil.getUserIdFromToken(email, token, "queryReadLater");
		if (userID.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.UNAUTHORIZED);
		}
		return ResponseEntity.ok(this.newsService.query(userID.get()));
	}

	@DeleteMapping(value = "/read-later/delete")
	public ResponseEntity<?> deleteReadLater(@RequestHeader("token") final String token,
			@RequestHeader("email") final String email, @RequestParam final String url) {
		final Optional<Integer> userID = AuthProviderApiUtil.getUserIdFromToken(email, token, "deleteReadLater");
		if (userID.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.UNAUTHORIZED);
		}
		this.newsService.deleteReadLater(userID.get(), url);
		return ResponseEntity.ok("entry deleted from user: " + userID.get());
	}
}