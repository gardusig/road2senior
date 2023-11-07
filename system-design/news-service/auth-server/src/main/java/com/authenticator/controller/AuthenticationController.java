package com.authenticator.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.authenticator.model.LoginRequest;
import com.authenticator.model.LoginResponse;
import com.authenticator.model.NewUserRequest;
import com.authenticator.model.ValidateResponse;
import com.authenticator.service.AuthenticationService;

@RestController
@RequestMapping(path = "/auth")
@CrossOrigin(origins = "*")
public class AuthenticationController {
	private final AuthenticationService authenticationService;

	@Autowired
	public AuthenticationController(final AuthenticationService authenticationService) {
		this.authenticationService = authenticationService;
	}

	@PostMapping(value = "/login")
	public ResponseEntity<?> login(@RequestBody final LoginRequest request) throws Exception {
		final String email = request.getEmail();
		if (!authenticationService.hasUserWithEmail(request.getEmail())) {
			return new ResponseEntity<>("user not found", HttpStatus.NOT_FOUND);
		}
		final ValidateResponse authorizedResponse = authenticationService.isUserAuthorized(email,
				request.getPassword());
		if (authorizedResponse.hasError()) {
			return new ResponseEntity<>(authorizedResponse.getErrorMessage(), HttpStatus.UNAUTHORIZED);
		}
		final ValidateResponse allowedResponse = authenticationService.isUserAllowed(email);
		if (allowedResponse.hasError()) {
			return new ResponseEntity<>(allowedResponse.getErrorMessage(), HttpStatus.FORBIDDEN);
		}
		final String token = authenticationService.generateToken(email);
		final LoginResponse loginRespose = new LoginResponse(token);
		return ResponseEntity.ok(loginRespose);
	}

	@GetMapping(value = "/validate/{email}/{token}/{op}")
	public ResponseEntity<?> validateToken(@PathVariable final String email, @PathVariable final String token,
			@PathVariable final String op) {
		final ValidateResponse validateTokenResponse = authenticationService.validateToken(email, token, op);
		if (validateTokenResponse.hasError()) {
			return new ResponseEntity<>(validateTokenResponse.getErrorMessage(), HttpStatus.UNAUTHORIZED);
		}
		return ResponseEntity.ok(authenticationService.getUser(email).getId());
	}

	@PostMapping(value = "/logout/{email}/{token}")
	public ResponseEntity<?> logout(@PathVariable final String email, @PathVariable final String token) {
		final ValidateResponse logoutResponse = authenticationService.logout(email, token);
		if (logoutResponse.hasError()) {
			return new ResponseEntity<>(logoutResponse.getErrorMessage(), HttpStatus.NOT_FOUND);
		}
		return ResponseEntity.ok("logged out");
	}

	@PostMapping(value = "/forget/password/{email}")
	public ResponseEntity<?> forgetPassword(@PathVariable final String email) {
		if (!authenticationService.hasUserWithEmail(email)) {
			return new ResponseEntity<>("user not found", HttpStatus.NOT_FOUND);
		}
		return ResponseEntity.ok(this.authenticationService.getPasswordResetToken(email));
	}

	@PutMapping(value = "/new/password/{token}")
	public ResponseEntity<?> newPassword(@PathVariable final String token, @RequestBody final LoginRequest request)
			throws Exception {
		final ValidateResponse hasPasswordResetTokenResponse = this.authenticationService
				.hasPasswordResetToken(request.getEmail(), token);
		if (hasPasswordResetTokenResponse.hasError()) {
			return new ResponseEntity<>(hasPasswordResetTokenResponse.getErrorMessage(), HttpStatus.NOT_FOUND);
		}
		final ValidateResponse resetPasswordResponse = this.authenticationService.resetPassword(request.getEmail(),
				request.getPassword());
		if (resetPasswordResponse.hasError()) {
			return new ResponseEntity<>(resetPasswordResponse.getErrorMessage(), HttpStatus.FORBIDDEN);
		}
		return ResponseEntity.ok("registered new password");
	}

	@PostMapping(value = "/new/user/")
	public ResponseEntity<?> newUser(@RequestBody NewUserRequest request) {
		final ValidateResponse createNewUserResponse = this.authenticationService.createNewUser(request.getName(),
				request.getEmail());
		if (createNewUserResponse.hasError()) {
			return new ResponseEntity<>(createNewUserResponse.getErrorMessage(), HttpStatus.FORBIDDEN);
		}
		return ResponseEntity.ok("registered new user");
	}

	@DeleteMapping(value = "/delete/user/{email}")
	public ResponseEntity<?> deleteUserWithEmail(@PathVariable final String email) {
		final ValidateResponse deleteUserResponse = this.authenticationService.deleteUser(email);
		if (deleteUserResponse.hasError()) {
			return new ResponseEntity<>(deleteUserResponse.getErrorMessage(), HttpStatus.NOT_FOUND);
		}
		return ResponseEntity.ok("user deleted");
	}
}